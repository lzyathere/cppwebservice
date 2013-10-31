GSOAP_ROOT=/usr/local/gSOAP
WSNAME0=soap
WSNAME=SmsWBS
CC=g++ -g -DWITH_NONAMESPACES
INCLUDE=-I $(GSOAP_ROOT)/include
SERVER_OBJS=$(WSNAME0)C.o $(WSNAME0)$(WSNAME)Service.o stdsoap2.o
CLIENT_OBJS=$(WSNAME0)$(WSNAME)Proxy.o $(WSNAME0)C.o stdsoap2.o
ALL_OBJS=${WSNAME}server.o $(WSNAME0)C.o $(WSNAME0)$(WSNAME)Service.o 

all:server

${WSNAME}.wsdl: ${WSNAME}.h
	$(GSOAP_ROOT)/bin/soapcpp2 -i -S ${WSNAME}.h

#   $? 列出当前目标所依赖的的文件列表中比当前目标文件还要新的文件
stdsoap2.o: $(GSOAP_ROOT)/src/stdsoap2.cpp 
	$(CC) -c $? $(INCLUDE)

$(ALL_OBJS):%.o:%.cpp 
	$(CC) -c $? $(INCLUDE)

server: ${WSNAME}.wsdl ${WSNAME}server.o $(SERVER_OBJS) 
	$(CC) ${WSNAME}server.o $(SERVER_OBJS) -o ${WSNAME}server


clean:
	rm -f *.o *.xml *.a *.wsdl *.nsmap $(WSNAME0)H.h $(WSNAME0)C.cpp $(WSNAME0)Server.cpp  $(WSNAME0)Stub.* $(WSNAME0)$(WSNAME)Service.* $(WSNAME0)ServerLib.cpp $(WSNAME)server ns.xsd
