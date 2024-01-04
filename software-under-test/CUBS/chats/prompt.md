# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of China Unicom Billing System (CUBS). CUBS is designed to calculate a phone bill based on a plan's type and fee, along with user's talk time and data usage. The source code of CUBS is as follows:

```java
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
}
```

Please identify the metamorphic relation of this function as much as possible and output them as java code. Each metamorphic relation should be named test[x], where [x] is the test case number. Here are some example:

```java
/**
 * Metamorphic Relation 1: If the talk time increases, the bill should not decrease.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test1(String planType, int planFee, int talkTime, int flow) {
    /* Get source output */
    BillCalculation CUBS = new BillCalculation();
    double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

    /* Construct follow-up input */
    int follow_talkTime = talkTime * 2;

    /* Get follow-up output */
    double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

    /* Verification */
    assertTrue(follow_out >= source_out);
}

/**
 * Metamorphic Relation 2: If the talk time decreases, the bill should not increase.
 */
@ParameterizedTest
@MethodSource("testcaseProvider")
public void test2(String planType, int planFee, int talkTime, int flow) {
    /* Get source output */
    BillCalculation CUBS = new BillCalculation();
    double source_out = CUBS.phoneBillCalculation(planType, planFee, talkTime, flow);

    /* Construct follow-up input */
    int follow_talkTime = talkTime / 2;

    /* Get follow-up output */
    double follow_out = CUBS.phoneBillCalculation(planType, planFee, follow_talkTime, flow);

    /* Verification */
    assertTrue(follow_out <= source_out);
}
```

## Chat 4...n

Please identify more different metamorphic relations of this program and codify them as java code.