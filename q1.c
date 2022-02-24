#include "local.h"
pthread_mutex_t ball_mutex;
  void throwandcatch(struct kids *);
  void throw(int );
  void catch(int );
  void checkifdone();
 struct kids kid[4];
 int endflag=0;
 int prntflag=0;

  
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
 int main(void){

 pthread_t kid_thread[4];
pthread_mutex_init(&ball_mutex, NULL);
 for (int i = 0; i < 4; i++) // lines
    {   
     if (i==0){
     kid[i].hasball=1;   
     } 
     else{
         kid[i].hasball=0;
     }
     kid[i].kid_id = i;
          
            if (pthread_create(&kid_thread[i], NULL, (void *)throwandcatch, &kid[i]) != 0)
            {
                perror("Failed to create thread");
                return 1;
            }
        }
        sleep(1);
        while(endflag!=1);
        printf("-------------GAME Over------------\n");
        //printf("===============================================================\n");
    }
    void throwandcatch(struct kids *kid){
    while(1){
    if (pthread_mutex_lock(&ball_mutex) == 0)
    {
        
        if(endflag ==1){
           
            pthread_mutex_unlock(&ball_mutex); 
            
            break;
        }
        if(kid->hasball==1){
         if(kid->kid_id!=3){
          printf("\n Kid %d throwing to kid %d \n",kid->kid_id,kid->kid_id+1);
         }
         else{
            printf("\n Kid %d throwing to kid 0 \n",kid->kid_id); 
         }
          printf("==============================================\n");
         // printf("--------------Current Drop for Kid %d is %d -----------------------\n",kid->kid_id,kid->balldropcnt);
         fflush(stdout);
          throw(kid->kid_id);
        }
        else{
         pthread_mutex_unlock(&ball_mutex); 
        }
       
    }
     else
    {
        printf("didn't lock\n");
       
        exit(-1);
    }
     pthread_mutex_unlock(&ball_mutex);
    }
    
    return;
    }
    void throw(int kid_id){
       sleep(1);
        srand(time(0));
        int random_number = rand() % 100 + 1;
        
       // printf("************in throw percent %d ********\n",random_number);
        if(random_number<=10){
            kid[kid_id].balldropcnt++;
            printf("kid %d has dropped the ball while throwing count= %d \n",kid_id,kid[kid_id].balldropcnt);
            fflush(stdout);
        }
        checkifdone();
        if(endflag !=1){
        catch( kid_id);
        }
        else{
            return;
        }
       return;
    }
    void catch(int kid_id){
        sleep(1);
        srand(time(0));
        int random_number = rand() % 100 + 1;
       
        if(random_number<=40){
             kid[kid_id+1].balldropcnt++;
              printf("kid %d missed the ball while catching count= %d\n",kid_id+1,kid[kid_id+1].balldropcnt);
               fflush(stdout);
        }

        if(kid_id !=3){
            kid[kid_id].hasball=0;
            kid[kid_id+1].hasball=1;

        }
        else{
           kid[kid_id].hasball=0;
           kid[0].hasball=1;
        }
    checkifdone();
    return;
    }
    
    void checkifdone(){
        for (int i=0; i<4; i++){
            if (kid[i].balldropcnt ==5){
                endflag=1;
            }
        }
        return;
    }



    
 
 