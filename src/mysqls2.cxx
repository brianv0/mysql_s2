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
#include "geos_c.h"
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

        fprintf(stderr, "In UDF");
        fprintf(stdout, "In UDF2");
        auto *geombuff1 = reinterpret_cast<unsigned char *>(args->args[0]);
        *length = 9;
        fprintf(stderr, "Preparing");
        const char* hexstr = "\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf0\x3f\x00\x00\x00\x00\x00\x00\x00\x40";
        GEOSGeometry *geom1;
        geom1 = GEOSGeomFromWKB_buf(
                reinterpret_cast<const unsigned char *>(hexstr),
                args->lengths[0]
        );
        auto typ = GEOSGeomTypeId(geom1);
        char buffer [10];
        sprintf(buffer, "type: %d", typ);
        return buffer;
//        char *encoded;
//        encoded = GEOSGeomToWKT(geom1);
//        fprintf(stderr, "Converted to wkt");
//        fprintf(stderr, encoded);
//        free(geom1);
///        size_t outputlength = 0;
///        char *encoded = base64_encode(reinterpret_cast<const unsigned char *>(geombuff1), args->lengths[0], &outputlength);
///        auto len = static_cast<unsigned long>(outputlength);
///        length = &len;
//        initid->ptr = encoded;
//        return encoded;
    }


    void UDF_API s2_contains_deinit(UDF_INIT *initid) {
        if (initid->ptr) {
            free(initid->ptr);
        }
        fflush(stderr);
    }

}