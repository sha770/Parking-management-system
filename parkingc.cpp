#include<iostream>
#include<vector>
#include<windows.h>
#include<fstream>
using namespace std;
// structure to store time
struct time
{
    int hh;
    int mm;
    int ss;
    char col1;
    char col2;
};

//structure to store date
struct date
{
  int day;
  int month;
  int year;
  char sym1;
  char sym2;
};

//main class
class vehicle
{
    string pltno;
    int type;
    date dt;
    time arrive;
    time departure;

public:
    void addVehicle();
    void deleteVehicle();
    void printvehicle(vehicle v);
    void show();


};

//vector to store vehicle details
vector<vehicle> veh(100);
int static totalvehicle=0,totalcar=0,totalbike=0,totalamt=0,i=0,space=10;

fstream file;

//function for adding vehicle
void vehicle::addVehicle()
{
    

      vehicle *v = new vehicle;
      cout<<"Enter vehicle type(1 for Car/2 for Bike) : ";
      cin>>v->type;
      cout<<"Enter vehicle number : ";
      cin>>v->pltno;
      cout<<"Enter arrival time in hours minutes and seconds : ";
      cin>>v->arrive.hh>>v->arrive.col1>>v->arrive.mm>>v->arrive.col2>>v->arrive.ss;
      cout<<"Enter date in day month and year: ";
      cin>>v->dt.day>>v->dt.sym1>>v->dt.month>>v->dt.sym2>>v->dt.year;

      veh.at(i).pltno=v->pltno;
      veh.at(i).type=v->type;
      veh.at(i).arrive.hh=v->arrive.hh;
      veh.at(i).arrive.mm=v->arrive.mm;
      veh.at(i).arrive.ss=v->arrive.ss;
      veh.at(i).dt.day=v->dt.day;
      veh.at(i).dt.month=v->dt.month;
      veh.at(i).dt.year=v->dt.year;
       if(totalvehicle<space){
      i++;
      totalvehicle++;

      if(v->type == 1)
      {
          totalcar++;
      }
      else
        {
        totalbike++;
        }

        cout<<"\nVehicle added successfully"<<endl;
}
}

//function to cacculate the duration of parking
 int computeTimeDifference(time t1,time t2)
  {

   int sec1, sec2, totalsec;
   time t3;
    //calculate difference
    //get time in total seconds
    sec1 = t1.hh*60*60 + t1.mm*60 + t1.ss;
    sec2 = t2.hh*60*60 + t2.mm*60 + t2.ss;

    totalsec = sec2-sec1;

    //extract time in Hours, Minutes and Seconds
    t3.mm = totalsec/60;
    t3.hh = t3.mm/60;
    t3.mm = t3.mm%60;
    t3.ss = totalsec%60;

   // cout<<"Time difference:" <<hh<<":"<<mm<<":"<<ss<<endl;
   return t3.hh;
}

// function to remove vehicle from parking lot and apply charge
  void vehicle:: deleteVehicle()
  {
      string pno;
      int typ;
      time depart;
      int time_diff;
      int charge=0;

      cout<<"Enter vehicle type(1 for Car/2 for Bike) : ";
      cin>>typ;
      cout<<"Enter vehicle number : ";
      cin>>pno;
      cout<<"Enter departure time in hours minutes and seconds : ";
      cin>>depart.hh>>depart.col1>>depart.mm>>depart.col2>>depart.ss;



      for(int j=0;j<=i;j++)
      {
          if((veh.at(j).pltno==pno)&&(veh.at(j).type==typ))
          {
              veh.at(j).departure.hh=depart.hh;
              veh.at(j).departure.mm=depart.mm;
              veh.at(j).departure.ss=depart.ss;

              time_diff=computeTimeDifference(veh.at(j).arrive,depart);

              if(veh.at(j).type== 1)
              {
                  totalcar--;
                  if(time_diff<2)
                  {
                      charge=20;
                  }
                  else
                  {
                      if((time_diff>2) && ((time_diff<5))){
                              charge=40;
                          }
                          else
                            {
                               charge=50;
                            }
                  }

              }
              else
              {
                  totalbike--;

                      if( time_diff<2)
                      {
                          charge=5;
                      }
                      else
                      {
                          if((time_diff>2) && ((time_diff<5)))
                              {
                                  charge=10;
                              }
                              else
                                {
                                   charge=20;
                                }
                      }

              }

              cout<<"\nVehicle having vehicle number  : "<<veh.at(j).pltno<<" has left the parking after paying Rs. "<<charge<<endl;
              file.open("parkingDatabase.txt",ios::app);
              if(!file)
                {
                    cerr << "Error: file could not be opened" << endl;
                    exit(1);
                }

               file<<veh.at(j).type<<"\t\t\t"<<veh.at(j).pltno<<"\t\t\t"<<veh.at(j).dt.day<<"/"<<veh.at(j).dt.month<<"/"<<veh.at(j).dt.year<<"\t\t\t"<< veh.at(j).arrive.hh<<":"<<veh.at(j).arrive.mm<<":"<<veh.at(j).arrive.ss<<"\t\t\t"<<veh.at(j).departure.hh<<":"<<veh.at(j).departure.mm<<":"<<veh.at(j).departure.ss<<endl;
               file.close();
              veh.erase(veh.begin()+j);
              i--;
              totalvehicle--;
              totalamt = totalamt+charge;
              break;

          }

          if(j==i)
          {
              cout<<"\nWrong Entry , Try Again "<<endl;
              cout<<"Departure : "<<endl;
              deleteVehicle();
          }

      }



  }

 
 //function to print the vechile detaile
  void vehicle::printvehicle(vehicle v)
  {
    cout<<v.type<<"\t\t\t"<<v.pltno<<"\t\t\t"<<v.dt.day<<"/"<<v.dt.month<<"/"<<v.dt.year<<"\t\t\t"<< v.arrive.hh<<":"<<v.arrive.mm<<":"<<v.arrive.ss<<endl;
  }
 
 //function for admin to track the details of parking
  void vehicle::show()
  {
      cout<<"Vehicle Type\t\tVehicle Number\t\t\tDate\t\t\tArrival Time"<<endl;
      for(int j=0;j<i;j++)
      {
          printvehicle(veh[j]);
      }
  }

//function to show total no vehicle parked
  void totalveh()
  {
      cout<<"Total number of vehicle parked : "<< totalvehicle<<endl;
      cout<<"Total number of car parked : "<< totalcar<<endl;
      cout<<"Total number of bike parked : "<<  totalbike<<endl;

  }
 

 //function for admin to know the collection 
  void totalamount()
  {
      cout<<"Total Collection till now : "<<totalamt<<endl;
  }

  void status(){
    if(totalvehicle<space)
    cout<<"***space is avialable***"<<endl;
    else
    cout<<"***parking lot is full***"<<endl;
  }

  int main()
  { 
    char choice;
    int choice2;
    char ans;
    int pass;
    system ( "cls" ) ;

  do
  {
     system ( "cls" ) ;
     cout<<"********************************************************************"<<endl;
     cout<<"                 VEHICLE PARKING RESERVATION SYSTEM                 "<<endl;
     
     cout<<"a-ARE YOU ADMIN?"<<endl
         <<"b-ARE YOU CUSTMORE?"<<endl
         <<"********************************************************************"<<endl
         <<"ENTER YOUR CHOICE"<<endl;
         cin>>choice;

         switch(choice){
            
            case 'a':cout<<"ENTER THE PASSWORD"<<endl;
                     cin>>pass;
                     if(pass==2022){
                        cout<<"1. Total number of vehicles parked"<<endl
                             <<"2. Departure of vehicle"<<endl
                             <<"3. Total Amount collected "<<endl
                             <<"4. Display "<<endl
                             <<"5. Exit"<<endl
                             <<"***************************************************"<<endl
                             <<"ENTER YOUR SUB CHOICE"<<endl;
                             cin>>choice2;
                    
                             switch(choice2){

                                case 1:system ( "cls" ) ;
                                       totalveh();
                                        break;
                                
                                case 2:system ( "cls" ) ;
                                      cout<<"Departure : "<<endl;
                                      veh.at(i).deleteVehicle();
                                      break;
                                
                                case 3:system ( "cls" ) ;
                                       totalamount();
                                        break;

                                case 4:system ( "cls" ) ;
                                       veh.at(i).show();
                                       break;  

                                case 5:exit(0);             
                             }

                     }
                     else
                     cout<<"**SORRY!!ACCESS NOT ALLOWED**"<<endl;
                     break;
            case 'b':cout<<"1.Check status"<<endl
                         <<"2.Do your entry"<<endl
                         <<"3.exit"<<endl
                         <<"****************************************************"<<endl
                         <<"ENTER YOUR SUBCHOICE"<<endl;
                         cin>>choice2;

                         switch(choice2){
                            case 1:system ( "cls" ) ;
                                   status();
                                   break;

                            case 2:system ( "cls" ) ;
                                   cout<<"Add : "<<endl;
                                   veh.at(i).addVehicle();
                                   break;
                            case 3:exit(0);       
                         }
                         break;
                         

         }
         cout<<"\nDo you want to continue, press y/n : "<<endl;
         cin>>ans;
         if(ans=='n')
         {
             break;
         }
         else
         {
             continue;
         }

  }while(1);

  return 0;
  }

