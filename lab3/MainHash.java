import java.io.*;



public class MainHash extends HashTableImp{
    public hashmain(int bucket) throws IOException {
        super(bucket);
    }

    public static void main(String[] args) throws IOException,ArithmeticException{

        int buckets=20;

        HashTableImp tab1=new HashTableImp(buckets);
        HashTableImp tab2=new HashTableImp(buckets);

        FileInputStream strm1 = new FileInputStream("sample-text1.txt ");
        FileInputStream strm2 = new FileInputStream("sample-text2.txt ");


        // Get the object of DataInputStream
        DataInputStream in1 = new DataInputStream(strm1);
        DataInputStream in2 = new DataInputStream(strm2);
        BufferedReader br1 = new BufferedReader(new InputStreamReader(in1));
        BufferedReader br2 = new BufferedReader(new InputStreamReader(in2));
        String strLine1;
        String letterLine1;
        String[] words1;



        String strLine2;
        String letterLine2;
        String[] words2;
        int i=0,j=0;

        //Read File Line By Line in file1
        while ((strLine1 = br1.readLine()) != null) {
            letterLine1 = strLine1.replaceAll("[^a-zA-Z0-9]", " ").toLowerCase().replaceAll("\\s+", " ");
            words1 = letterLine1.split(" ");

            while (words1.length > i) {
                tab1.insert(words1[i]);
                i++;

            }

            i = 0;

        }

        //Read File Line By Line in file2
        while ((strLine2 = br2.readLine()) != null) {
            letterLine2 = strLine2.replaceAll("[^a-zA-Z0-9]", " ").toLowerCase().replaceAll("\\s+", " ");
            words2 = letterLine2.split(" ");

            while (words2.length > j) {
                tab2.insert(words2[j]);
                j++;

            }

            j = 0;

        }





        //tab1.print();


        }












    }





