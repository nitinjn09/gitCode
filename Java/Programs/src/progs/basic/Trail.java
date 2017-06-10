package progs.basic;

public class Trail {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
/*		System.out.println("Hello");
		outer:
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					for (int k = 0; k <10; k++) {
						System.out.println("Value of k is " +k);
						break outer;
					}
				}
			} */
		int inum = 1_00_00_000;
        System.out.println("inum:" + inum);

        long lnum = 1_00_00_000;
        System.out.println("lnum:" + lnum);

        float fnum = 2.10_001F;
        System.out.println("fnum:" + fnum);

        double dnum = 2.10_12_001;
        System.out.println("dnum:" + dnum);

	}

}

