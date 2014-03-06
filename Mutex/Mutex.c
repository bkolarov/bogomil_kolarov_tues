#include <stdio.h>
#include <pthread.h>


int common = 0;

pthread_mutex_t sum_mutex;

void* sum(void *arg) {
    int i;
    for(i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&sum_mutex);
        common++; 
        pthread_mutex_unlock(&sum_mutex);
   }
    
    pthread_exit(NULL);

}

int main() {
    pthread_t first, second;
       
    pthread_create(&first, NULL, sum, NULL);
    pthread_create(&second, NULL, sum, NULL);

    pthread_join(first, NULL);
    pthread_join(second, NULL);

    printf("%d\n", common);

    return 0;
}
