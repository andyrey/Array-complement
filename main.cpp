#include <iostream>
#include <limits.h>
#include <random>
using  namespace std;
/*
bool is_same_sign(int a, int b)
{
    bool bss= ((a>=0 && b>=0) || (a<=0 && b<=0))? true:false;
    cout<<"is " <<a<<" same sign as "<<b<<" ? "<<bss<<"\n";
    return bss;
}*/

int null_finding(const int elements_number, const int* sequence, int& first_zero_position)
{//how many zeros in init sequenced- 0, 1 or >1 ?
    int null_number=0;
    for(int i=0; i< elements_number; ++i)
    {
        if (sequence[i]== 0)
        {
            ++null_number;
            first_zero_position=i;
        }
        if(null_number > 1)
            break;//case all output will be zeros
    }
    return null_number;
}

bool multiply_AxB(const int numb, int& product)
{//multiply 1 number by another with  range precautions
    //skip calc when 0 element!
    if(numb && abs(product) > (INT_MAX / abs(numb)))
    {
        cout<<"multiplication interrupted " <<product<< " due to "<<"\n";
        cout<< "INT_MAX or INT_MIN exceeding"<<endl;
        return false;
    }
    else
    {
        if(numb)//skip calc when 0-valued element!
            product *= numb;
        else
            product= 1*product;
        return true;
    }
}

bool multiply_array(const int elements_number,const int* sequence, int* result_sequence, int& prod)
{// calc product of array and fills resulting array

    bool result = true;//будем оптимистами
    int zero_pos;//проверка на наличие нулей в массиве
    int null_number= null_finding(elements_number, sequence,zero_pos);
    if(null_number)
        cout<<endl<< "position of  zero "<<zero_pos<<"; zeros number in sequence "<<null_number<<endl;
    if(null_number < 2)// один ноль найден или нет вообще
    {
        for(int i=0; i< elements_number; ++i)
        {
            if(!multiply_AxB(sequence[i],prod))//вышли за пределы при умножении
            {
                cout<<"Mult# "<<i<<" Product was "<<prod<<" ";
                result= false;
                break;
            }
        }
        cout<<"\n";
    }
    else
        prod=0;

    if(result)
    {
        for(int i=0; i< elements_number; ++i)
        {
            if(null_number == 0)
                result_sequence[i]=prod/sequence[i];
            else
                result_sequence[i]=0;
        }
        if(null_number == 1)//the single non-zero element
        {
            //cout<< "fzp "<<first_zero_pos<<" prod "<<prod<<endl;
            result_sequence[zero_pos]= prod;
        }
    }
    return result;
}

int main()
{
    int elements_number=0;
    ////values limitation
    int max= 21;//INT_MAX/1024;
    int min= -21;//INT_MIN/1024;
    int maximal_size= 11;//avoid int limit exceeding while multiplication!
    ////random distribution preparing
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

    /////user input for array size up to 11
    do
    {
        cout << "Input number of elements from 2 up to "<<maximal_size<<endl;
        cout << "Input 0 to quit the program"<<endl;
        cin >> elements_number;
        cout<<"You entered "<<elements_number<<endl;
        if(elements_number<1)
            return 0;
    }while(elements_number> maximal_size || elements_number <2 );
    /////end of user input for array size up to 20

    ////initial array generating & populating
    /// for debugging
    /*
    elements_number=7;
    int a[7]={2, 6,  10, -9, 4, 0, 1};
    int b[7];
    cout<<" Primery array has elements:"<<endl;
    for(int i=0; i < elements_number; ++i)
        cout<<a[i]<<"; " ;
    */
    ////end of debugging

    int *a = new int[elements_number];
    int *b = new int[elements_number];
    cout<<" Primery array has elements:"<<endl;
    for(int i=0; i < elements_number; ++i)
    {
        auto random_output = uni(rng);
        a[i]=random_output;
        cout<<a[i]<<"; " ;
    }
    cout<<endl;
    ////end of init array generating & populating

    ////multiplication & result array calculating
    bool success= false;
    int product=1;

    success= multiply_array(elements_number,a,b, product)  ;
    cout<<"success= "<< success<<"\n";

    //// result demostration
    if (success)
    {
        cout<<"Product result  "<< product<<endl;
        cout<<"Resulting array "<< endl;
        for(int i=0; i < elements_number; ++i)
            cout<<b[i]<<" ";
    }
    cout<<"\n\n";

    ////heap cleaning
    if(a) delete [] a;
    if(b) delete [] b;
}
