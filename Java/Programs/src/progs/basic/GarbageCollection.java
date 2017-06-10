package progs.basic;
//import java.lang.*;

public class GarbageCollection {

	public static void main(String[] args) {
		int g1[] = { 0, 1, 2, 3, 4, 5 };
        System.out.println(g1[1] + " ");
 
        // Requesting Garbage Collector
        System.gc();
        System.out.println("Hey I just requested "+
                          "for Garbage Collection");

	}

}
