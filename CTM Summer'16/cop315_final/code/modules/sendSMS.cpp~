/*******************************************
@ author: Saurabh
@ project: COP315
*******************************************/

#include <Python.h>
#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <queue>   
#include <fstream>
#include <unistd.h>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
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
      //int count_1 =0;
      //while(count_1 !=12){
	      string sql;
	      sql = "SELECT * FROM lprs_db.smstable WHERE sent = '0' ORDER BY id limit 2;";

	      /* create a non-transactional object */
	      nontransaction N(C);

	      /*execute the query and fetch result */
	      result R(N.exec(sql));
	      /* using queue to store id of violations to be marked as resolved later */
	      queue<string> str_id;
	      ofstream myfile("../logs/log.txt",ios_base::out);
	      if(myfile.is_open()){
		cout<<"file opened";		
	      }
	      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		myfile<< "send to = "<< c[4].as<string>() <<endl;
		cout<<"send to = "<< c[4].as<string>() <<endl;
		myfile<<"message = "<<c[2].as<string>() <<endl;
		cout<< "message = "<<c[2].as<string>() <<endl;

		str_id.push(c[0].as<string>());
		myfile<<" "<<endl;
		cout<<" "<<endl;
	      }
	      myfile.close();
	      /* end nontransaction */
	      N.abort();
	      /* read commit error if this is not aborted */
		Py_Initialize();
		PyRun_SimpleString("import sys");
		PyRun_SimpleString("sys.path.append(\"../code/modules/\")");

		cout<<endl<<" open smspy ";
		pName = PyString_FromString("smspy");
		
		pModule = PyImport_Import(pName);
		
		if(pModule == NULL) {
		    PyErr_Print();
		    Py_Finalize();
		    return 0;
		}
		
		// Clean up
		Py_DECREF(pModule);
		Py_DECREF(pName);

		// Finish the Python Interpreter
		Py_Finalize();

	      while(!str_id.empty()){
		sql = "UPDATE lprs_db.smstable SET sent = '1' WHERE id = '"+str_id.front() +"';";
		str_id.pop();
		work W(C);
		W.exec(sql);
		W.commit();
	      }
	      //count_1++;
	      sleep(1);
      //}
	      
      /*disconnect*/
      C.disconnect();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}
