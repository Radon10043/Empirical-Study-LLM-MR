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
}
