pooltest:testPool.cpp MysqlConnPool/MysqlConn.cpp MysqlConnPool/MysqlConn.h MysqlConnPool/ConnPool.cpp MysqlConnPool/ConnPool.h
	g++ testPool.cpp MysqlConnPool/MysqlConn.cpp MysqlConnPool/MysqlConn.h MysqlConnPool/ConnPool.cpp MysqlConnPool/ConnPool.h -o pooltest -ljsoncpp -lmysqlclient
 