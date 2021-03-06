/* 
 * File:   vsql_pgsql.h
 * Author: vitor
 *
 * Created on April 17, 2013, 8:22 PM
 */

#ifndef VSQL_CONNECTION_PGSQL_H
#define	VSQL_CONNECTION_PGSQL_H
#define PARAM_STR 1
#define PARAM_INT 2
#define PARAM_FLOAT 3
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <libpq-fe.h>
#include "vsql_types.h"

namespace VSQL_PGSQL {

    class Statement {
    private:
        std::string _queryString;
        PGconn * _conn;
        PGresult * _result_set;
        Row _row;
        ResultSet _result;
        int _total_rows;
        int _total_cols;
        void clearResultSet();
    public:
        Statement(std::string sql, PGconn * conn);
        void bindParam(void * value, int data_type);
        void bindValue(std::string param, void * value, int data_type);
        bool execute();
        Row fetch();
        ResultSet fetchAll();
        int rowCount();
        int columnCount();
    };

    class Connection {
    private:
        std::string _host;
        std::string _user;
        std::string _passwd;
        std::string _dbname;
        int _port;
        bool _in_transaction;
        PGconn * _conn;
        PGresult * _result_set;
        std::string _error_message;
        void clearResultSet();

    public:
        Connection(std::string host, std::string user, std::string passwd, std::string dbname, int port);
        bool openConnection();
        bool beginTransaction();
        bool savePointTransaction(std::string savePointName);
        bool commitTransaction();
        bool rollbackTransaction();
        bool rollbackTransaction(std::string savepoint);
        bool exec(std::string sql);
        VSQL_PGSQL::Statement * prepare(std::string sql);
        VSQL_PGSQL::Statement * query(std::string sql);
        bool closeConnection();
        std::string getErrorMessage();
        std::string getServerVersion();
    };
}

#endif	/* QUERY_H */

