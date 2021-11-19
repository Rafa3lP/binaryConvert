#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int* binarySum(unsigned int b1[], unsigned int b2[], int bits);
unsigned int* getBinaryComplement(unsigned int b1[], int bits);
void printBinary(unsigned int b[], int bits);
int intBinarySignConvert(int num, int bits);
void printErr(char *programa);

int main(int argc, char *argv[]){

    if(argc > 1){

        int r, bits;
        int n = atoi(argv[1]);
        if(argc == 3){

            bits = atoi(argv[2]);

            if(bits == 8 || bits == 16 || bits == 32 || bits == 64){

                r = intBinarySignConvert(n, bits);

            }else{

                printErr(argv[0]);

            }

        }else{

            r = intBinarySignConvert(n, 16);

        }
        
        if(r == -1){

            printf("nao e possivel representar");

        }

        return 0;

    }else{

        printErr(argv[0]);

        return 0;

    }

}

unsigned int* binarySum(unsigned int b1[], unsigned int b2[], int bits){

    unsigned int *result;
    int s, i;
    result = (unsigned int*) malloc(sizeof(unsigned int)*bits);
    
    if(result == NULL) exit(EXIT_FAILURE);

    for(i = bits - 1; i >= 0; i--){

        s = b1[i] + b2[i];

        switch(s){

            case 0:
                result[i] = 0;
                break;
            case 1:
                result[i] = 1;
                break;
            case 2:
                result[i] = 0;
                if((i-1) >= 0) b1[i-1]++;
                break;
            default:
                exit(EXIT_FAILURE);
                break;

        }

    }

    return result;

}

unsigned int* getBinaryComplement(unsigned int b1[], int bits){

    unsigned int *complement;
    int i;

    complement = (unsigned int*) malloc(sizeof(unsigned int)*bits);
    if(complement == NULL) exit(EXIT_FAILURE);

    for(i = 0; i < bits; i++){

        complement[i] = (b1[i] == 0) ? 1 : 0;

    }

    return complement;

}

void printBinary(unsigned int b[], int bits){

    int a = 1, j;
    for(j = 0; j < bits; j++){

        printf("%d", b[j]);

        if(a == 4){

            printf(" ");
            a = 0;

        }
        a++;

    }

}

int intBinarySignConvert(int num, int bits){

    double range = pow(2, bits);
    double nRange = range/2;
    double pRange = nRange-1;
    int r, d, j;
    unsigned int *v, *converted, *complement, *negative, i, a;
    unsigned int binaryOne[bits];

    if(num >= 0){

        if(num <= pRange){

            v = (unsigned int*) malloc(sizeof(unsigned int));
            if(v == NULL) exit(EXIT_FAILURE);
            converted = (unsigned int*) malloc(sizeof(unsigned int)*bits);
            if(converted == NULL) exit(EXIT_FAILURE);
            i = 0;
            d = num;

            while(d != 0 && d != 1){

                r = d % 2;
                d = d / 2;

                v[i++] = r;

                v = (unsigned int *) realloc(v, (sizeof(unsigned int)*(i+1)));
                
            }

            v[i] = d;

            for(j = 0; j < bits; j++){

                converted[j] = 0;

            }
            a = i;
            for(j = bits-(i+1); j < bits; j++){

                converted[j] = v[a--];

            }

            //imprimindo valor binario
            printBinary(converted, bits);

        }else{

            return -1;

        }

    }else{

        if(num >= (-1)*nRange){

            v = (unsigned int *) malloc(sizeof(unsigned int));
            if(v == NULL) exit(EXIT_FAILURE);
            converted = (unsigned int *) malloc(sizeof(unsigned int)*bits);
            if(converted == NULL) exit(EXIT_FAILURE);
            i = 0;
            d = -num;

            while(d != 0 && d != 1){

                r = d % 2;
                d = d / 2;

                v[i++] = r;

                v = (unsigned int *) realloc(v, (sizeof(unsigned int)*(i+1)));
                

            }

            v[i] = d;
            for(j = 0; j < bits; j++){
                
                converted[j] = 0;

            }
            a = i;
            for(j = bits-(i+1); j < bits; j++){

                converted[j] = v[a--];

            }

            //calcular complemento
            complement = getBinaryComplement(converted, bits);

            for(j = 0; j < bits; j++){

                binaryOne[j] = (j == bits-1) ? 1 : 0;

            }

            negative = binarySum(complement, binaryOne, bits);

            printBinary(negative, bits);

        }

    }

    free(v);
    free(converted);
    free(complement);
}

void printErr(char *programa){

    printf("Erro\n");
    printf("A sintaxe deve ser:\n");
    printf("%s <numeroASerConvertido> [numeroDeBits]\n", programa);
    printf("onde numeroASerConvertido e um inteiro e\n");
    printf("numeroDeBits e opcional e deve ter o valor de 8, 16, 32 ou 64\n");
    printf("o padrao e 16 bits\n");

}