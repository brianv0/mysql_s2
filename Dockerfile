FROM mysql:latest

RUN apt-get -qq update 
RUN apt-get install -y build-essential pkg-config git pkg-config cmake libgflags-dev libgoogle-glog-dev libgtest-dev libssl-dev libmariadbclient-dev-compat

RUN \
    # mysql-udf-http
    git clone --recurse-submodules https://github.com/brianv0/mysql_s2.git \
    && cd mysql_s2/ \
    && cmake . \
    && make \
    && cp src/libmysqls2.so /usr/lib/mysql/plugin/
