/*********************************************
 * CO322: Data structures and algorithms
 * Implementation of the hashTable
 *********************************************/
import java.io.*;

class Node{

    public String key;
    public int value;
    Node next;          
 
    public Node(String key, int value){

        this.key = key;
        this.value = value;
        this.next = null;
    }

    public int getValue(){

        return value;
    }
}

class HashTableImp implements HashTable {

    /* Put your code here */

    private Node[] table;
    private int buckets;
    private int size; 
    
 
    public int HashCode(String key){

        int i = 0;
        for (char c : key.toCharArray()){
            i += 31*c + i;
        }

        return i;
    }
     
    public HashTableImp(int buckets){
    // create a open hash table with given number of buckets 

	    size = 0;
        this.buckets = buckets;
        table = new Node[this.buckets]; 

        for (int i = 0; i < this.buckets; i++)
        {
            table[i] = null;
        }
    }

        
    private int stringCode(String x ){
        
        int hashValue = HashCode(x);
        hashValue %= this.buckets;

        if (hashValue < 0)
        {
            hashValue += this.buckets;
        }

        return hashValue;
    }
    
    public void insert(String key){

        int hash = (stringCode( key ) % this.buckets);
        HashTableImp ht = new HashTableImp(this.buckets);
        int value = ht.getCount(key);

        if (table[hash] == null)
        {
            table[hash] = new Node(key, value);
        }
        else
        {
            Node entry = table[hash];

            while (entry.next != null && !entry.key.equals(key))
            {
                entry = entry.next;
            }

            if (entry.key.equals(key))
            {
                entry.value += 1;            
            }
            else
            {
                entry.next = new Node(key, value);
            }                      
        }

        size++;
    }
    
    public int getCount(String key){
        
        int hash = (stringCode( key ) % this.buckets);

        if (table[hash] == null)
        {
            return 1;
        }
        else 
        {
            Node entry = table[hash];

            while (entry != null && !entry.key.equals(key))
            {
                entry = entry.next;
            }

            if (entry == null)
            {
                return 0;
            }
            else
            {
                return entry.value;
            }
        }
    }
   
    public void PrintSizes(){

        int count;  
        System.out.println();

        for (int i = 0; i < this.buckets; i++)
        {
            count = 0;

            Node entry = table[i];

            while (entry != null)
            {
                count += 1;
                entry = entry.next;
            }
            System.out.print(count);
            System.out.println();
        }
    }
    
    public void printHashTable(){

        int count;  

        for (int i = 0; i < this.buckets; i++)
        {
            count = 0;
            System.out.print("\nBucket "+ (i + 1) +" : ");
            Node entry = table[i];

            while (entry != null)
            {
                count += 1;
                System.out.print(entry.key +"("+ entry.value + ")" +" ");
                entry = entry.next;
            }
            System.out.print("\nThe Size is: " + count + "");
        }
    }

    public int search(String key){

        int bucket = hashone(key,buckets);

        Node list = table[bucket];
        while (list != null) {

            if (list.key.equals(key))
                return list.value;
            list = list.next;
        }

        return 0;
    }

    public static int hashone(String word,int buckets){

            char ch[];
            ch = word.toCharArray();
            int wordlength = word.length();

            int i, sum;
            for (sum = 0, i = 0; i < word.length(); i++)
                sum += ch[i];

                    return sum % buckets;

    }
}// end HashTableImp 
