package src;
public class AirlinesBaggageBillingService
{

    int airClass = 0;

    int area = 0;

    double luggage = 0;

    double benchmark = 0;

    double takealong = 0;

    double luggagefee = 0;

    int tln = 0;

    boolean isStudent = false;

    double economicfee = 0;

    public double feeCalculation( int airClass, int area, boolean isStudent, double luggage, double economicfee )
    {
        this.airClass = this.preairclass( airClass );
        
        this.area = this.prearea( area );
        
        switch (this.airClass) {
        case 0 :
            benchmark = 40;
            break;

        case 1 :
            benchmark = 30;
            break;

        case 2 :
            benchmark = 20;
            break;

        case 3 :
            benchmark = 0;
            break;

        }
        if (this.area == 1) {
            takealong = 7;
            tln = 1;
            if (isStudent) {
                benchmark = 30;
            }
        }
        if (this.area == 0) {
            switch (this.airClass) {
            case 0 :
                tln = 2;
                takealong = 5;
                break;

            case 1 :
                tln = 1;
                takealong = 5;
                break;

            case 2 :
                tln = 1;
                takealong = 5;
                break;

            case 3 :
                tln = 1;
                takealong = 5;
                break;

            }
        }
        if (benchmark>luggage){ 

        	luggage=benchmark;
        }
        return luggagefee = (luggage - benchmark) * economicfee * 0.015;
    }

    public int preairclass( int airClass )
    {
        int result = 0;
        result = airClass % 4;
        return result;
    }

    public int prearea( int area )
    {
        int result = 0;
        result = area % 2;
        return result;
    }

    public int getAirClass() {
        return airClass;
    }

    public void setAirClass(int airClass) {
        this.airClass = airClass;
    }

    public int getArea() {
        return area;
    }

    public void setArea(int area) {
        this.area = area;
    }

    public double getLuggage() {
        return luggage;
    }

    public void setLuggage(double luggage) {
        this.luggage = luggage;
    }

    public double getBenchmark() {
        return benchmark;
    }

    public void setBenchmark(double benchmark) {
        this.benchmark = benchmark;
    }

    public double getTakealong() {
        return takealong;
    }

    public void setTakealong(double takealong) {
        this.takealong = takealong;
    }

    public double getLuggagefee() {
        return luggagefee;
    }

    public void setLuggagefee(double luggagefee) {
        this.luggagefee = luggagefee;
    }

    public int getTln() {
        return tln;
    }

    public void setTln(int tln) {
        this.tln = tln;
    }

    public boolean isStudent() {
        return isStudent;
    }

    public void setStudent(boolean isStudent) {
        this.isStudent = isStudent;
    }

    public double getEconomicfee() {
        return economicfee;
    }

    public void setEconomicfee(double economicfee) {
        this.economicfee = economicfee;
    }
}
