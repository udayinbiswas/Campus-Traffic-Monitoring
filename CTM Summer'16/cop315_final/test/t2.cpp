#include <Python.h>
#include <string>
#include <iostream>
using namespace std;
int main(int argc,char** argv){
string phno = "9891990199";
string message = "hello there ";
string string1 =
"import serial, time, sys\n\
port='/dev/ttyACM0'\n\
ser = serial.Serial(port,9600,timeout=5)\n\
if ser.isOpen():\n\
	ser.close()\n\
ser.open()\n\
ser.flushInput();\n\
time.sleep(0.5)\n\
while 1==1:\n\
	j1= ser.readline() \n\
	if len(j1)!=0:\n\
		break\n\
";
string string2  ="num=";
string2 = string2+"'"+phno+"$"+"'";
string string3=
"num=str(num)\n\
ser.write(num.encode())\n\
";
string string4 ="msg=";
string4=string4+"'"+message+"$" +"'";
string string5 =
"ser.write(msg.encode())\n\
count = 0\n\
j=''\n\
while count<1:\n\
	j=ser.readline()\n\ 
	if len(j)!=0:\n\
		count = count+1\n\
";
string string6=
"ser.close()\n\
";
 
Py_Initialize();
PyObject *pModule = PyImport_AddModule("__main__");
PyRun_SimpleString(string1.c_str());
string pp ="y";
while(1){
	cin>>pp;
	if(pp.compare("q")==0){
		break;
	}
	cin>>phno;
        cin>>message;
	string2  ="num=";
	string2 = string2+"'"+phno+"$"+"'";
	PyRun_SimpleString(string2.c_str());
	PyRun_SimpleString(string3.c_str());
	string4 ="msg=";
	string4=string4+"'"+message+"$" +"'";
	PyRun_SimpleString(string4.c_str());
	PyRun_SimpleString(string5.c_str());
	PyObject *catcher = PyObject_GetAttrString(pModule,"j");
	//PyErr_Print();
	string s6 = PyString_AsString(catcher);
	cout<<s6<<endl;
	if(s6.substr(0,8).compare("Success!")==0){
        	cout<<"pika pika"<<endl;
		}
	}
PyRun_SimpleString(string6.c_str());	
Py_Finalize();
return 0;

 
	
}
