#include "soapSmsWBSService.h"
#include "SmsWBS.nsmap"

int http_get(struct soap *soap);

int main(int argc, char **argv)
{ 
  	SmsWBSService calc;
	calc.fget = http_get;
  if (argc < 2)
    calc.serve();	/* serve as CGI application */
  else
  { 
	int port = atoi(argv[1]);
    if (!port)
    { 
	fprintf(stderr, "Usage: calcserver++ <port>\n");
      exit(0);
    }
	fprintf(stderr, "port为,%d\n",port);
    /* run iterative server on port until fatal error */
	
	
    while (1)
    { 
	
	int err = calc.run(port);
	if(err < 0)
	{
	fprintf(stderr,"服务运行出错: %d\n",err);
	calc.soap_stream_fault(std::cerr);
      	exit(-1);
	}
    }
  }
  return 0;
} 

int http_get(struct soap *soap) 
{ 
        FILE*fd = NULL;

	char *s = strchr( soap->path, '?' );
         if( !s || strcmp( s, "?wsdl" ) ){
             return SOAP_GET_METHOD;
         }

        fd = fopen("SmsWBS.wsdl", "rb"); //open WSDL file to copy
        if (!fd)
        {
                return 404; //return HTTP not found error
        }
        soap->http_content = "text/xml";  //HTTP header with text /xml content
        soap_response(soap,SOAP_FILE);
        for(;;)
        {
                size_t r = fread(soap->tmpbuf,1, sizeof(soap->tmpbuf), fd);
                if (!r)
                {
                        break;
                }
                if (soap_send_raw(soap, soap->tmpbuf, r))
                {
                        break; //cannot send, but little we can do about that
                }
        }
        fclose(fd);
        soap_end_send(soap);
        return SOAP_OK; 
}

int SmsWBSService::add(int a, int b, int *result)
{ 
	*result = a + b;
  	return SOAP_OK;
} 
