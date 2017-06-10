package progs.basic;

public class NullInJava {

	private static Object obj;
	//int a = 10;
	public static void main(String[] args) {
		/*
		// compile-time error : can't find symbol 'NULL'
        Object obj = NULL; 
         
        //runs successfully
        Object obj1 = null;  */
		
		// it will print null;
        System.out.println("Value of object obj is : " + obj);
        //System.out.println(a);

	}

}
