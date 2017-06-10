package progs.basic;

class Animal1 {
	Animal1() {
		System.out.println("Animal is created");
	}
}

class Dog1 extends Animal1 {
	void eat() {
		System.out.println("Dog is playing");
	}
	Dog1() { 
		System.out.println("Dog is created");
	}
}

public class SuperExample {

	public static void main(String[] args) {
		Dog1 d = new Dog1();
		d.eat();
	}

}
