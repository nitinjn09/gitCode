package progs.basic;

class Animal{ 
	int age;
	void eat() {
		System.out.println("Animal eating...");
	}  
}  

class Dog extends Animal {  
	String breed;
	void bark() {
		System.out.println("Dog barking...");
	}  
}  

class Cat extends Animal {
	int higth;
	void meow() {
		System.out.println("Cat meowing..");
	}
}

class BabyDog extends Dog {
	String coour;
	void weep() {
		System.out.println("Baby dog weeping..");
	}
}

class InheritanceExamples {  
	public static void main(String args[]) {
		System.out.println("Simple Inheritance Example");
		Dog d=new Dog();  
		d.bark();  
		d.eat();  
		d.age = 3;
		System.out.println();
		
		System.out.println("Multilevel Inheritance Example");
		BabyDog bd = new BabyDog();
		bd.eat();
		bd.bark();
		bd.weep();
		System.out.println();
		
		System.out.println("Hierarchical Inheritance Example");
		Dog d1 = new Dog();
		Cat c1 = new Cat();
		d1.bark();
		c1.meow();
		c1.eat();
		System.out.println();
		
	}
} 
