#if defined _WIN32 || defined __CYGWIN__
#   define UDF_API __declspec(dllUDF_API)
#   define UDF_LOCAL
#else
#   if HAVE_ATTRIBUTE_VISIBILITY
#       define UDF_API __attribute__ ((visibility("default")))
#       define UDF_LOCAL __attribute__ ((visibility("hidden")))
#   else
#       define UDF_API
#       define UDF_LOCAL
#   endif
#endif

#include <mysql.h>
#include <cstdlib>
#include <cstdio>
#include "base64/base64.h"
#include "s2/s2boolean_operation.h"
#include "s2/s2cap.h"
#include "s2/s1angle.h"
#include "s2/s2latlng.h"
#include "s2/s2latlng_rect.h"


extern "C" {

#ifndef NDEBUG
#define LOG(...) fprintf(stderr, __VA_ARGS__);
#else
#define LOG(...)
#endif


    my_bool UDF_API s2_contains_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
    char UDF_API *s2_contains(UDF_INIT *initid, UDF_ARGS *args, char *result,
                                   unsigned long *length, char *is_null, char *error);
    void UDF_API s2_contains_deinit(UDF_INIT *initid);

    my_bool UDF_API s2_contains_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
        my_bool const_item = 1;

        if (args->arg_count != 2) {
            snprintf(message, MYSQL_ERRMSG_SIZE, "s2_contains expects 2 spherical geometry pairs");
            return 1;
        } else if (args->arg_type[0] != STRING_RESULT && args->arg_type[1] != STRING_RESULT) {
            snprintf(message, MYSQL_ERRMSG_SIZE, "s2_contains expects 2 s2 spherical geometry pairs");
            return 1;
        }
        initid->maybe_null = 1;
        initid->const_item = const_item;
        initid->ptr = 0;
        return 0;
    }

    char UDF_API *s2_contains(UDF_INIT *initid, UDF_ARGS *args, char *result,
                                   unsigned long *length, char *is_null, char *error) {
        size_t outputlength = 0;
        const char *geom1 = args->args[0];
        char *encoded = base64_encode(reinterpret_cast<const unsigned char *>(geom1), args->lengths[0], &outputlength);
        unsigned long len = static_cast<unsigned long>(outputlength);
        length = &len;
        initid->ptr = encoded;
        return encoded;
    }

    void UDF_API s2_contains_deinit(UDF_INIT *initid) {
        if (initid->ptr) {
            free(initid->ptr);
        }
    }

}