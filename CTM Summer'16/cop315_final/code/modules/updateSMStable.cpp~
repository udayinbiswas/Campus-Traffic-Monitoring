/*******************************************
@ author: Saurabh
@ project: COP315
*******************************************/


#include <iostream>
#include <pqxx/pqxx> 
#include <string>
#include <queue>   
#include <map>
#include <utility>  
#include <unistd.h>
using namespace std;
using namespace pqxx;

int main(int argc, char* argv[])
{
   try{
      connection C("dbname=lprs_db user=lprs password=lprs\
      hostaddr=127.0.0.1 port=5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }
      int count_1=0;
      while(count_1 !=12){
	/* Sql query goes here buddy!!! */
	      string sql;
	      sql = "SELECT * FROM lprs_db.smart_events WHERE resolved = 0 AND (speed_violation = 1 OR wwd_violation=1 OR lane_violation = 1 OR park_violation = 1 );";

	      /* create a non-transactional object */
	      nontransaction N(C);

	      /*execute the query and fetch result */
	      result R(N.exec(sql));
	      /* using queue to store id of violations to be marked as resolved later */
	      queue<string> str_id;
	      map<string,string> m;
	      for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		str_id.push(c[0].as<string>());
		if(m.find(c[1].as<string>()) == m.end()){
		  m[c[1].as<string>()]="license plate: "+ c[1].as<string>()+" ";	
		  m[c[1].as<string>()] = m[c[1].as<string>()]+ c[2].as<string>() +" ";
		  if((c[3].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "wwd Violation ";	
		  }	
		  if((c[4].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "speed Violation ";
			m[c[1].as<string>()]= m[c[1].as<string>()]+ c[6].as<string>();	
		  }
		  if((c[8].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "lane Violation ";	
		  }
		  if((c[9].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "park Violation ";	
		  }
		}
		else{
		  m[c[1].as<string>()] = m[c[1].as<string>()]+" " + c[4].as<string>() +" ";
		  if((c[3].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "wwd Violation ";	
		  }	
		  if((c[4].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "speed Violation ";	
			m[c[1].as<string>()]= m[c[1].as<string>()]+ c[6].as<string>();
		  }
		  if((c[8].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "lane Violation ";	
		  }
		  if((c[9].as<string>()).compare("1") == 0 ){
			m[c[1].as<string>()]= m[c[1].as<string>()]+ "park Violation ";	
		  }
		}
		m[c[1].as<string>()]= m[c[1].as<string>()]+ " http://localhost/?transid="+ c[0].as<string>();
		 
	      }

	      // typedef map<string,string>::iterator it_type;
	      // for(it_type iterator = m.begin(); iterator != m.end(); iterator++) {
	      //   cout<< iterator->first <<":"<< iterator->second <<endl;
	      // } 
	      typedef map<string,string>::iterator it_type;
	      map<pair<string,string>,pair<string,string> > m3w;    // 3 way map
	      for(it_type iterator = m.begin(); iterator != m.end(); iterator++) {
		  sql = "SELECT * FROM registered_users WHERE vehicle_number ='"+ iterator->first+"';";
		  result R1(N.exec(sql));
		  if(R1.begin()!= R1.end()){
		  	  result::const_iterator c = R1.begin();
			  pair<string,string> pt (iterator->first,iterator->second);
			  pair<string,string> pt2 (c[3].as<string>(),c[2].as<string>());	
			  m3w[pt]=pt2;
		  }
		  pair<string,string> pt (iterator->first,iterator->second);		  
		//pair<string,string> pt2 ("7503759013","smartcampusiitd@gmail.com");	
           	  //m3w[pt] = pt2;
		  	  
	      }

	      /* end nontransaction */
	      N.abort();
	      /* read commit error if this is not aborted */

	      /* insert into SMS table */
	      typedef map<pair<string,string>,pair<string,string> >::iterator it_type1;      
	      for(it_type1 iterator1 = m3w.begin(); iterator1 != m3w.end(); iterator1++) {
		  sql = "INSERT INTO lprs_db.smstable(vehicle_number, message,phone_number,email) VALUES ('"+iterator1->first.first +"','"+iterator1->first.second+"','"+ iterator1->second.first+"','"+iterator1->second.second+"');";
		  work W(C);
		  W.exec(sql);
		  W.commit();
	      }
	      
	      /*mark as resolved in enter violation */

	      while(!str_id.empty()){
		sql = "UPDATE lprs_db.smart_events SET resolved = 1 WHERE transid = '"+str_id.front() +"';";
		str_id.pop();
		work W(C);
		W.exec(sql);
		W.commit();
	      }
	      count_1++;
              sleep(5);
      }
	      

      /*disconnect*/
      C.disconnect();
   }catch (const std::exception &e){
      cerr << e.what() << std::endl;
      return 1;
   }
}
