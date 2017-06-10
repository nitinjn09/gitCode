package progs.basic;

class Bank {
	//float rateOfInterest;
	float getRateOfInterest() {
		return 0;
	}
}

class SBI extends Bank {
	float getRateOfInterest() {
		return 8.6f;
	}
}

class CITIBANK extends Bank {
	float getRateOfInterest() {
		return 8.65f;
	}
}

class HDFC extends Bank {
	float getRateOfInterest() {
		return 8.5f;
	}
}

public class MethodOverridingExample {

	public static void main(String[] args) {
		SBI sbi = new SBI();
		CITIBANK citi = new CITIBANK();
		HDFC hdfc = new HDFC();
		
		System.out.println("SBI ROI: " +sbi.getRateOfInterest());
		System.out.println("CITIBANK ROI: " +citi.getRateOfInterest());
		System.out.println("HDFC ROI: " +hdfc.getRateOfInterest());
		
	}

}
