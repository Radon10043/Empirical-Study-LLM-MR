import java.io.IOException;

public class BillCalculation
{

    private String planType = "";

    private int planFee = 0;

    private int talkTime = 0;

    private int flow = 0;

    private int callViewTime = 0;

    private double talkTimePer = 0;

    private double flowPer = 0.3;

    private double viewPer = 0.6;

    private int talkTimeBench = 0;

    private int flowBench = 0;

    private double bill = 0;

    public double phoneBillCalculation( String planType, int planFee, int talkTime, int flow )
    {
        if (planType == "A" || planType == "a") {
            switch (planFee) {
            case 46 :
                talkTimeBench = 50;
                flowBench = 150;
                talkTimePer = 0.25;
                break;

            case 96 :
                talkTimeBench = 96;
                flowBench = 240;
                talkTimePer = 0.15;
                break;

            case 286 :
                talkTimeBench = 286;
                flowBench = 900;
                talkTimePer = 0.15;
                break;

            case 886 :
                talkTimeBench = 3000;
                flowBench = 3000;
                talkTimePer = 0.15;
                break;
			case 990:
				break;

            default  :
                new IOException( "Invalid planFee!" );

            }
        } else {
            if (planType == "B" || planType == "b") {
                switch (planFee) {
                case 46 :
                    talkTimeBench = 120;
                    flowBench = 40;
                    talkTimePer = 0.25;
                    break;

                case 96 :
                    talkTimeBench = 450;
                    flowBench = 80;
                    talkTimePer = 0.15;
                    break;

                case 126 :
                    talkTimeBench = 680;
                    flowBench = 100;
                    talkTimePer = 0.15;
                    break;

                case 186 :
                    talkTimeBench = 1180;
                    flowBench = 150;
                    talkTimePer = 0.15;
                    break;

                default  :
                    new IOException( "Invalid planFee" );

                }
            } else {
                new IOException( "Invalid planType!" );
            }
        }
        if (talkTime < talkTimeBench) {
            talkTime = talkTimeBench;
        }
        if (flow < flowBench) {
            flow = flowBench;
        }
        bill = (talkTime - talkTimeBench) * talkTimePer + (flow - flowBench) * flowPer + planFee;
        //bill = (talkTimeBench) * talkTimePer + (flow - flowBench) * flowPer + planFee;
        return bill;
    }


    public static void main(String[] args) {
        BillCalculation b = new BillCalculation();
        System.out.println(b.phoneBillCalculation("b", 46, 3685, 3261));
    }
}
