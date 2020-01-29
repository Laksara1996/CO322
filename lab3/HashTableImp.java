import java.io.*;

/*********************************************
 * CO322: Data structures and algorithms
 * Implementation of the hashTable
 *********************************************/
class HashTableImp implements HashTable {


    /* Put your code here */

    // Node for the linked list
    static private class ListNode {
        String key;
        int value;
        ListNode next;
    }

    int buckets=20;
    int count=0;

    private ListNode[] table;  // The hash table, represented as an array of linked lists.


    public HashTableImp(int buckets) throws IOException {

        table = new ListNode[buckets];      // create a open hash table with given number of buckets

    }// end HashTableImp





    @Override
    public void insert(String key) {


        int bucket = hashtwo(key,buckets);   //location of the key

        ListNode list = table[bucket]; // For traversing the linked list at the appropriate location.

        while (list != null) {
            // Search the nodes in the list, to see if the key already exists.
            if (list.key.equals(key))
                break;
            list = list.next;
        }

        // At this point, either list is null, or list.key.equals(key).
        if (list != null) {
            //  found the key and change the value.
            list.value = list.value+1;
        }

        else {
            //  the key is in the list. Add a new node at the head of the list to contain the new key and its  value.

            ListNode newNode = new ListNode();
            newNode.key = key;
            newNode.value = 1;
            count++;
            newNode.next = table[bucket];
            table[bucket] = newNode;

        }

    }

    @Override
    public int search(String key) {

        int bucket = hashone(key,buckets);   //location of the key

        ListNode list = table[bucket]; // For traversing the linked list at the appropriate location.
        while (list != null) {
            // Check and return if the specified key is in the node that list points to.
            if (list.key.equals(key))
                return list.value;
            list = list.next;  // Move to next node in the list.
        }
        //else  the key is not in the table.
        return 0;

    }

/*    public void print() {

        for(int i=0;i<buckets;i++){
            ListNode list = table[i]; // For traversing the linked list at the appropriate location.
            int count=0;
            while (list != null) {
                // Check and return if the specified key is in the node that list points to.
                count++;
                //System.out.println(list.key);

                list = list.next;  // Move to next node in the list.
            }
            //System.out.println("bucket no "+ i + " no of keys "+ count);
            System.out.print(count+ ",");


            count=0;

        }
    }
*/


    public static int hashone(String word,int buckets){



            char ch[];
            ch = word.toCharArray();
            int wordlength = word.length();

            int i, sum;
            for (sum = 0, i = 0; i < word.length(); i++)
                sum += ch[i];

                    return sum % buckets;


    }


    public int hashtwo(String word,int buckets) {
        int intLength = word.length() / 4;
        long sum = 0;
        for (int j = 0; j < intLength; j++) {
            char c[] = word.substring(j * 4, (j * 4) + 4).toCharArray();
            long mult = 1;
            for (int k = 0; k < c.length; k++) {
                sum += c[k] * mult;
                mult *= 256;
            }
        }

        char c[] = word.substring(intLength * 4).toCharArray();
        long mult = 1;
        for (int k = 0; k < c.length; k++) {
            sum += c[k] * mult;
            mult *= 256;
        }

        return (int) (Math.abs(sum) % buckets);


    }

}