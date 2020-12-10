#include "bloom_filter.h"

//gobal var
int m;			//bit cell
int k;			// hash function
uint32_t seed;		//changes to create new functions
int hold_hash[];	//h1...hk
int fill_array[];	//ints to fill  
int Bloom_fil[100];	//  
int Clear_array[];



void set_num_hashf (int k1)	//will set num hash functions
{
    m = 4294967295;
    k = k1;
    seed = 12;
    int i=0;
    int temp[k];
    hold_hash= temp[k];
    fill_array=temp[k];
    Clear_array=temp[k];
    for(i=0; i<100;i++)//0-100 fill with 0
    {
        Bloom_fil[i]=0;
        if(i<k)
        {
            Clear_array[i]=0;
        }
    }
    
}

int Hash(string obj_name, uint32_t seed) // hash strings using mrmurhash
{
        int return_hash=0;
        uint32_t hash[1];
        char string_hash[11]; 
        //hash using Murmur
        const char *key = obj_name.c_str();
        MurmurHash3_x86_32(key, (uint32_t) strlen(key), seed, hash); //cout<< "hash" <<hash[0] <<" = ";
    
        // transform uint32_t to char
        snprintf(string_hash, sizeof string_hash, "%lu", (unsigned long)hash[0]); //cout<< "hash in string"<<string_hash <<endl ;
        
        //convert char to int inverse of first two 
        int tens = string_hash[1] - '0';
        int ones = string_hash[0] - '0';
        return_hash= tens*10+ones;
        return return_hash;
}
int hash_k[] (string obj_name)	// creates k num of has functions
{
    int temp[k];	//hold to return 
    uint32_t seed_hold = seed;	//gives different hashs depending on seed val
    
    //hash same obj using different seeds
    for(int i = 0; i < k; i++)	//gives h1(obj_name), ... ,hk(obj_name)stores in vec
    {
        temp[i]=Hash(obj_name,seed_hold);
        seed_hold++;
        //cout<<"temp  "<<temp[i]<<endl;
    }
    return temp;
}

void transform_hash()	// since vector size 0-99 need only 2 values: first and last digit (combined)
{
    fill_array=hold_hash;
    //delete  hold_hash
    hold_hash.clear ();

}
void fill_Bloom()
{
    for (int i = 0; i < k; i++)
    {
        Bloom_fil[fill_array[i]] = 1;
    }
    fill_array=Clear_array;
}

void insert (string obj_name) //insert hash to bloom
{
    hold_hash = hash_k(obj_name);
    transform_hash();
    fill_Bloom();
}

bool query (string obj_name) // check if hash is in bloom 1=true 0 =false
{
hold_hash = hash_k (obj_name);
    transform_hash ();
    for (int i = 0; i < k; i++)
    {
        if (Bloom_fil[fill_array[i]] == 0)
            {
                //cout<<"f"<<endl;
            return false;
            }

    }
    fill_array=Clear_array;
    //cout<<"t"<<endl;
    return true;
}