import java.util.Scanner;

public class MealOrderingSystem {

	private int numberOfRequestedBundlesOfFlowers;
	
	private int numberOfChildPassengers;
	
	private int numberOfFirstClassSeats;
	
	private int numberOfBusinessClassSeats;
	
	private int numberOfEconomicClassSeats;
	
	private int numberOfCrewMembers;
	
	private int numberOfPilots;
	
	public MSR msr;
	
	public MSR generateMSR(String aircraftmodel,String changeinthenumberofcrewmembers,
			int newnumberofcrewmembers, String changeinthenumberofpilots, int newnumberofpilots,
			int numberofchildpassengers,int numberofrequestedbundlesofflowers){
		
		this.msr = new MSR();
		
		if(aircraftmodel.equals("747200")){
			numberOfFirstClassSeats = 0;
			numberOfBusinessClassSeats = 20;
			numberOfEconomicClassSeats = 150;
			numberOfCrewMembers = 10;
			numberOfPilots = 2;
			numberOfChildPassengers = numberofchildpassengers;
			numberOfRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers;
			
		}else if(aircraftmodel.equals("747300")){
			numberOfFirstClassSeats = 5;
			numberOfBusinessClassSeats = 25;
			numberOfEconomicClassSeats = 200;
			numberOfCrewMembers = 12;
			numberOfPilots = 3;
			numberOfChildPassengers = numberofchildpassengers;
			numberOfRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers;
			
		}else if(aircraftmodel.equals("747400")){
			numberOfFirstClassSeats = 10;
			numberOfBusinessClassSeats = 30;
			numberOfEconomicClassSeats = 240;
			numberOfCrewMembers = 14;
			numberOfPilots = 3;
			numberOfChildPassengers = numberofchildpassengers;
			numberOfRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers;
			
		}else if(aircraftmodel.equals("000200")){
			numberOfFirstClassSeats = 0;
			numberOfBusinessClassSeats = 35;
			numberOfEconomicClassSeats = 210;
			numberOfCrewMembers = 13;
			numberOfPilots = 2;
			numberOfChildPassengers = numberofchildpassengers;
			numberOfRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers;
			
		}else if(aircraftmodel.equals("000300")){
			numberOfFirstClassSeats = 10;
			numberOfBusinessClassSeats = 40;
			numberOfEconomicClassSeats = 215;
			numberOfCrewMembers = 14;
			numberOfPilots = 3;
			numberOfChildPassengers = numberofchildpassengers;
			numberOfRequestedBundlesOfFlowers = numberofrequestedbundlesofflowers;
			
		}else{
			new java.io.IOException( "Invalid stafflevel" );
			
		}
		
		if(changeinthenumberofcrewmembers.equals("y")){
			numberOfCrewMembers = newnumberofcrewmembers;
			
		}
		
		if(changeinthenumberofpilots.equals("y")){
			numberOfPilots = newnumberofpilots;
			
     	}
		
		this.msr.numberOfFirstClassMeals = this.numberOfFirstClassSeats * 2;
		this.msr.numberOfBusinessClassMeals = this.numberOfBusinessClassSeats * 2;
		this.msr.numberOfEconomicClassMeals = this.numberOfEconomicClassSeats * 2;
		this.msr.numberOfMealsForCrewMembers = this.numberOfCrewMembers * 2;
		this.msr.numberOfMealsForPilots = this.numberOfPilots * 2;
		this.msr.numberOfChildMeals = this.numberOfChildPassengers * 2;
		this.msr.numberOfBundlesOfFlowers = this.numberOfRequestedBundlesOfFlowers;
		
		return this.msr;

	}
	
public static void main(String args[]){
		
		Scanner s = new Scanner(System.in);
		String aircraftmodel = null;
		System.out.println("please enter aircraft model:\n");
		aircraftmodel = s.next();
		System.out.println("if there is a change in the number of crew members, enter\"y\". Otherwise, enter\"n\"\n");
		String changeInTheNumberOfCrewMembers = s.next();
		int numberofcrewmembers;
		if(changeInTheNumberOfCrewMembers.equals("y")){
			System.out.println("please enter new number of crew memebers:\n");
			numberofcrewmembers = s.nextInt();		
		}else{
			numberofcrewmembers = 0;
		}
		
		System.out.println("if there is a change in the number of pilots, enter\"y\". Otherwise, enter\"n\"\n");
		String changeInTheNumberOfPilots = s.next();
		int numberofpilots;
		if(changeInTheNumberOfPilots.equals("y")){
			System.out.println("please enter new number of crew memebers:\n");
			numberofpilots = s.nextInt();		
		}else{
			numberofpilots = 0;
		}
		System.out.println("please enter number of child passengers:\n");
		int numberOfChildPassengers = s.nextInt();
		System.out.println("please enter number of requested bundles of flowers:\n");
		int numberOfRequestedBundlesOfFlowers = s.nextInt();
		MealOrderingSystem sys = new MealOrderingSystem();
		MSR order = sys.generateMSR(aircraftmodel, changeInTheNumberOfCrewMembers, numberofcrewmembers, changeInTheNumberOfPilots, numberofpilots, numberOfChildPassengers, numberOfRequestedBundlesOfFlowers);
		
		System.out.println("Number of first-class meals: " + String.valueOf(order.numberOfFirstClassMeals + "\n"));
		System.out.println("Number of business-class meals: " + String.valueOf(order.numberOfBusinessClassMeals + "\n"));
		System.out.println("Number of economic-class meals: " + String.valueOf(order.numberOfEconomicClassMeals + "\n"));
		System.out.println("Number of meals for crew members : " + String.valueOf(order.numberOfMealsForCrewMembers + "\n"));
		System.out.println("Number of meals for pilots : " + String.valueOf(order.numberOfMealsForPilots + "\n"));
		System.out.println("Number of child meals : " + String.valueOf(order.numberOfChildMeals + "\n"));
		System.out.println("Number of bundles of flowers : " + String.valueOf(order.numberOfBundlesOfFlowers + "\n"));
	}
}
