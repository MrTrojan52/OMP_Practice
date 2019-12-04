#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpich/mpi.h>

#define MAX_DATA_SIZE 100
#define DELAY_BEFORE_SEND 3

int main( int argc, char* argv[] )
{
    int nSize;
    int nRank;
    char pMessage[MAX_DATA_SIZE];
    char pRecvBuff[MAX_DATA_SIZE];
    MPI_Init(&argc, &argv);

    
    
    MPI_Comm_size(MPI_COMM_WORLD, &nSize); 

    MPI_Comm_rank( MPI_COMM_WORLD, &nRank ); 
    sprintf(pMessage, "Hello from %d!", nRank);
    int nBufSize = strlen(pMessage);

    if( nRank==0 ) 
    {
        printf("Total processes count = %d\n", nSize );
    }

    MPI_Barrier(MPI_COMM_WORLD);

    while (1)
    {
        if (nRank == 0)
        {
            MPI_Send(pMessage, nBufSize, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
            MPI_Recv(pRecvBuff, MAX_DATA_SIZE, MPI_CHAR, nSize - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d Received:\n\t%s (%ld chars)\n\n", nRank, pRecvBuff, strlen(pRecvBuff));
            sleep(DELAY_BEFORE_SEND);
        }
        else
        {
            
            MPI_Recv(pRecvBuff, MAX_DATA_SIZE, MPI_CHAR, nRank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d Received:\n\t%s (%ld chars)\n\n", nRank, pRecvBuff, strlen(pRecvBuff));
            int nNext = -1;
            if (nRank != (nSize - 1))
            {
                nNext = nRank + 1;
            }
            else
            {
                nNext = 0;
            }
            sleep(DELAY_BEFORE_SEND);
            MPI_Send(pMessage, nBufSize, MPI_CHAR, nNext, 1, MPI_COMM_WORLD);
            
        }
    }
    
    MPI_Finalize();

    return 0;
} 