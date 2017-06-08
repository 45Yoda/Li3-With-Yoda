package engine;

import java.util.Comparator;
import java.io.Serializable;

public class ComparatorBytes implements Comparator<Artigo>, Serializable {

    public int compare(Artigo a1, Artigo a2){
            long bytes1 = a1.getBytes();
            long bytes2 = a2.getBytes();

            if(bytes1 <= bytes2) return 1;
            if(bytes1 > bytes2) return -1;
            else return 0;
   }
}