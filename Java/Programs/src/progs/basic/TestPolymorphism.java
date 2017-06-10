package progs.basic;

class Bank2 {
	float getROI() {
		return 0;
	}
}

class SBI2 extends Bank2 {
	float getROI() {
		return 8.6f;
	}
}

class ICICI extends Bank2 {
	float getROI() {
		return 8.65f;
	}
}

public class TestPolymorphism {
	public static void main (String args[]) {
		System.out.println("Hi");
		Bank2 b = new SBI2();
		System.out.println("SBI ROI :" +b.getROI());
		Bank2 b1 = new ICICI();
		System.out.println("ICICI ROI :" +b1.getROI());
	}
}

