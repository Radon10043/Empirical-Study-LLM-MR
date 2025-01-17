package src;

import java.io.IOException;
import java.util.Scanner;

public class ExpenseReimbursementSystem {
	
	private String levelOfSalesStaff;//"seniormanager","manager","supervisor"
	
	private double allowableMileage;
	
	private double costPerKilometer;
		
	public double calculateReimbursementAmount(String stafflevel, double actualmonthlymileage, double monthlysalesamount, double airfareamount, double otherexpensesamount){
		
		double feeForOverUseOfCar;
		
		double airfareReimbursement;
		
		double reimbursementsOtherThanAirfare;
		
		if(stafflevel.equals("seniormanager")){
			
			allowableMileage = 4000;
			costPerKilometer = 5;
			if(actualmonthlymileage < allowableMileage){
				
				actualmonthlymileage = allowableMileage;
			}
		
		}else if(stafflevel.equals("manager")){
			
			allowableMileage = 3000;
			costPerKilometer = 8;
			if(actualmonthlymileage < allowableMileage){
				
				actualmonthlymileage = allowableMileage;
			}
		}else if(stafflevel.equals("supervisor")){
			
			allowableMileage = 0;
			costPerKilometer = 0;
	
		}else{
			
			new java.io.IOException( "Invalid stafflevel" );
			
		}
		
		feeForOverUseOfCar = costPerKilometer*(actualmonthlymileage - allowableMileage);
		
		if(stafflevel.equals("seniormanager")) {
			
			airfareReimbursement = airfareamount;
			
		}else if(stafflevel.equals("manager")){
			
			if(monthlysalesamount >= 50000){
				
				airfareReimbursement = airfareamount;
				
			}else{
				
				airfareReimbursement = 0;
				
			}
			
		}else if(stafflevel.equals("supervisor")){
			
			if(monthlysalesamount >= 80000){
				
				airfareReimbursement = airfareamount;
				
			}else{
				airfareReimbursement = 0;
				
			}
			
		}else{
			
			new java.io.IOException( "Invalid stafflevel" );
			airfareReimbursement = 0;
		}
		
		if(monthlysalesamount >= 100000){
			
			reimbursementsOtherThanAirfare = otherexpensesamount;
			
		}else{
			
			reimbursementsOtherThanAirfare = 0;
			
		}
		
		double totalReimbursementAmount = - feeForOverUseOfCar + airfareReimbursement + reimbursementsOtherThanAirfare;
		
		return totalReimbursementAmount;
	}
	
	
	public static void main(String args[]){
		
		Scanner s = new Scanner(System.in);
		String stafflevel = null;
		System.out.println("please enter stafflevel:");
		stafflevel = s.next();
		System.out.println("please enter actual monthly mileage:");
		double actualmonthlymileage = s.nextDouble();
		System.out.println("please enter monthly sales amount:");
		double monthlysalesamount = s.nextDouble();
		System.out.println("please enter airfare:");
		double airfare = s.nextDouble();
		System.out.println("please enter other expenses:");
		double otherexpenses = s.nextDouble();
		ExpenseReimbursementSystem sys = new ExpenseReimbursementSystem();
		double amount = sys.calculateReimbursementAmount(stafflevel,actualmonthlymileage,monthlysalesamount,airfare,otherexpenses);
		System.out.println("total reimbursement amount: " + String.valueOf(amount));
		
	}	


	/* Added by Radon */
	public static double getAllowableMileageForStaffLevel(String staffLevel) throws IOException {
		if (staffLevel.equals("seniormanager")) {
			return 4000;
		} else if (staffLevel.equals("manager")) {
			return 3000;
		} else if (staffLevel.equals("supervisor")) {
			return 0;
		} else {
			throw new java.io.IOException("Invalid stafflevel");
		}
	}


	public static double getCostPerKilometerForStaffLevel(String staffLevel) throws IOException {
		if (staffLevel.equals("seniormanager")) {
			return 5;
		} else if (staffLevel.equals("manager")) {
			return 8;
		} else if (staffLevel.equals("supervisor")) {
			return 0;
		} else {
			throw new java.io.IOException("Invalid stafflevel");
		}
	}

	
	public static double getThresholdForAirfareReimbursement(String staffLevel) throws IOException {
		if (staffLevel.equals("seniormanager")) {
			return 0;
		} else if (staffLevel.equals("manager")) {
			return 50000;
		} else if (staffLevel.equals("supervisor")) {
			return 80000;
		} else {
			throw new java.io.IOException("Invalid stafflevel");
		}
	}

	public static double getThresholdForOtherExpensesReimbursement() {
		return 100000;
	}

	public static double calculateCarOveruseFee(String staffLevel, double actualMonthlyMileage) throws IOException {
		double allowableMileage = getAllowableMileageForStaffLevel(staffLevel);
		double costPerKilometer = getCostPerKilometerForStaffLevel(staffLevel);
		if (actualMonthlyMileage < allowableMileage) {
			actualMonthlyMileage = allowableMileage;
		}
		return costPerKilometer * (actualMonthlyMileage - allowableMileage);
	}
}
