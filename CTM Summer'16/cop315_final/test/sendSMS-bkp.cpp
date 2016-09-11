/*******************************************
@ author: Saurabh
@ project: COP315
*******************************************/


#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <queue>   
#include <fstream>
#include <unistd.h>
#include <Python.h>
using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
string phno = "";
string message = " ";
string string1 =
"import serial, time, sys\n\
port='/dev/ttyACM0'\n\
ser = serial.Serial(port,9600,timeout=13)\n\
if ser.isOpen():\n\
	ser.close()\n\
ser.open()\n\
ser.flushInput();\n\
time.sleep(0.5)\n\
";
string string2;
string string3=
"ser.write(num.encode())\n\
";
string string4;
string string5 =
"ser.write(msg.encode())\n\
j=''\n\
j=ser.readline()\n\
ser.close()\n\
";

	

   try{
      connection C("dbname=lprs_db user=lprs password=lprs\
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      /* Sql query goes here buddy!!! */
      sleep(2);	
      int count_1 =0;
      while(count_1 !=30){
	      string sql;
	      sql = "SELECT * FROM lprs_db.smstable WHERE sent = '0';";

	      /* create a non-transactional object */
	      nontransaction N(C);

	      /*execute the query and fetch result */
	      result R(N.exec(sql));
	      /* using queue to store id of violations to be marked as resolved later */
	      queue<string> str_id;
	      queue<string> succe;
	      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		string2  ="num=";
		phno = c[4].as<string>();
                message = c[2].as<string>();
		string2 = string2+"'"+phno+"$"+"'";
		string4 ="msg=";
		string4=string4+"'"+message+"$" +"'";
		Py_Initialize();
		PyObject *pModule = PyImport_AddModule("__main__");
		PyRun_SimpleString(string1.c_str());
		PyRun_SimpleString(string2.c_str());
		PyRun_SimpleString(string3.c_str());
		PyRun_SimpleString(string4.c_str());
		PyRun_SimpleString(string5.c_str());
		PyObject *catcher = PyObject_GetAttrString(pModule,"j");
		//PyErr_Print();
		string s6 = PyString_AsString(catcher);
		succe.push(s6.substr(0,4));
		Py_Finalize();				
		//myfile<< "send to = "<< c[4].as<string>() <<endl;
		//cout<<"send to = "<< c[4].as<string>() <<endl;
		//myfile<<"message = "<<c[2].as<string>() <<endl;
		//cout<< "message = "<<c[2].as<string>() <<endl;
		str_id.push(c[0].as<string>());
		//myfile<<" "<<endl;
		//cout<<" "<<endl;
	      }
	      //myfile.close();
	      /* end nontransaction */
	      N.abort();
	      /* read commit error if this is not aborted */

	      while(!str_id.empty()){
		string temp_s = succe.front();		
		if(temp_s.compare("Succ")==0){
			sql = "UPDATE lprs_db.smstable SET sent = '1' WHERE id = '"+str_id.front() +"';";
			work W(C);
			W.exec(sql);
			W.commit();			
		}		
		str_id.pop();
	      }
	      count_1++;
	      sleep(2);
      }
	      
      /*disconnect*/
      C.disconnect();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}
