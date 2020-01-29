import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main{

    public static int buckSize;

    HashTableImp hashTable = new HashTableImp(buckSize);
    
    
    public void Read(String fileName)    
    {
        BufferedReader bReader=null;
        FileReader fRead=null;
        
     	try 
        {

            String [] words;

            fRead = new FileReader(fileName);
            bReader = new BufferedReader(fRead);
                          	
            for(String line = bReader.readLine(); line != null; line = bReader.readLine())
            {
                words = line.split(" ");

                for(String key: words)
                {
                    key = key.replaceAll("[^a-zA-Z]", "");
                    key = key.toLowerCase();
                    hashTable.insert(key);
                }                              
	        }
            
	       if(fRead != null) fRead.close();
	       if(bReader != null) bReader.close();


           hashTable.printHashTable();
           hashTable.PrintSizes();

	    }

        catch (IOException e) 
        {
                System.out.println(e);
                System.exit(-1);
        }
    }
    
    public static void main(String[] args){
        
        buckSize = 40;
        Main text = new Main();
        text.Read("sample-text2.txt");
        
    }
}
