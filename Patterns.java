public class Patterns{
    static class Pattern1{
        public void printPattern(){
            for(int i = 0; i < 5; i++) // row number is 5
            {
                for(int j = 0; j < 5; j++)
                {
                    if(j <= i)
                    {
                        System.out.printf("*");
                    }
                }
                System.out.printf("\n");
            }
        }
    }
    static class Pattern2{
        public void printPattern(){
            for(int i = 0; i < 5; i++)
            {
                for(int j = 4; j >= 0; j--)
                {
                    if(j > i)
                    {
                        System.out.printf(" ");
                    }
                    else
                    {
                        System.out.printf("*");
                    }
                }
                System.out.printf("\n");
            }
        }
    }

    static class Pattern3{
        public void printPattern(){
            for(int i = 5; i > 0; i--)
            {
                for(int j = 5; j > 0; j--)
                {
                    if(i >= j)
                    {
                        System.out.printf("*");
                    }
                }
                System.out.printf("\n");
            }
        }
    }

    static class Pattern4{
        public void printPattern(){
            for(int i = 5; i > 0; i--)
            {
                for(int j = 5; j > 0; j--)
                {
                    if(i >= j)
                    {
                        System.out.printf("*");
                    }
                    else
                    {
                        System.out.printf(" ");
                    }
                }
                System.out.printf("\n");
            }
        }
    }

    static class Pattern5{
        public void printPattern(){
            for(int i = 0; i < 5; i++)
            {
                for(int j = 5; j > i; j--)
                {
                    System.out.printf(" ");
                }

                for(int j = 0; j < 2*i + 1; j++)
                {
                    System.out.printf("*");
                }
                System.out.printf("\n");
            }
        }
    }

    static class Pattern6{ 
        public void printPattern(){
            int x = 0;
            for(int i = 5; i > 0; i--)
            {
                for(int j = 0; j < 2*i - 1; j++)
                {
                    for(int k = 0; k < x && j == 0; k++)
                    {
                        System.out.printf(" ");
                    }
                    System.out.printf("*");
                }
                x++;
                System.out.printf("\n");
            }
        }
    }

    static class Pattern7{ 
        public void printPattern(){
            for(int i = 0; i < 5; i++)
            {
                for(int j = 5; j > i; j--)
                {
                    System.out.printf(" ");
                }

                for(int j = 0; j < 2*i - 1; j++)
                {
                    System.out.printf("*");
                }
                System.out.printf("\n");
            }
            int x = 0;
            for(int i = 5; i > 0; i--)
            {
                for(int j = 0; j < 2*i - 1; j++)
                {
                    for(int k = 0; k < x && j == 0; k++)
                    {
                        System.out.printf(" ");
                    }
                    System.out.printf("*");
                }
                x++;
                System.out.printf("\n");
            }
        }
    }

    static class Pattern8{
        public void printPattern(){
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    if(j <= i)
                    {
                        System.out.printf("*");
                    }
                }
                System.out.println();
            }

            for(int i = 5; i > 0; i--)
            {
                for(int j = 0; j < i-1; j++)
                {
                    System.out.printf("*");
                }
                System.out.println();
            }
        }
    }

    static class Pattern9{
        public void printPattern(){
            for(int i = 0; i < 5; i++)
            {
                for(int j = 4; j >= 0; j--)
                {
                    if(j > i){
                        System.out.printf(" ");
                    }
                    else
                    {
                        System.out.printf("*");
                    }
                }
                System.out.println();
            }

            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    if(j > i){
                        System.out.printf("*");
                    }
                    else
                    {
                        System.out.printf(" ");
                    }
                }
                System.out.println();
            }
        }
    }

    static class Pattern10{
        public void printPattern(){
            int k = 0;
            int z = 9;
            for(int i = 5; i > 0; i--)
            {
                for(int j = z--; j > 0; j--)
                {
                    if(j <= i + k)
                    {
                        System.out.printf("*");
                    }
                    else
                    {
                        System.out.printf(" ");
                    }
                }
                System.out.println();
                k++;
            }
        }
    }

    static class Pattern11{
        public void printPattern(){
            int k = 5;
            int z = 5;
            for(int i = 0; i < 5 ; i++)
            {
                for(int j = z--; j < 10; j++)
                {
                    if(j < i + k)
                    {
                        System.out.printf(" ");
                    }
                    else
                    {
                        System.out.printf("*");
                    }
                }
                System.out.println();
                k--;
            }
        }
    }

    static class Pattern12{
        public void printPattern(){
            for(int i = 5; i > 0; i--)
            {
                for(int j = 0; j < i; j++)
                {
                    System.out.printf("*");
                }
                System.out.println();
            }

            for(int i = 1; i < 5; i++)
            {
                for(int j = 0; j <= i; j++)
                {
                    System.out.printf("*");
                }
                System.out.println();
            }
        }
    }

    static class Pattern13{
        public void printPattern(){
            for(int i = 0; i < 5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    if(j >= i)
                    {
                        System.out.printf("*");
                    }
                    else
                    {
                        System.out.printf(" ");
                    }
                }
                System.out.println();
            }

            for(int i = 4; i > 0; i--)
            {
                for(int j = 0; j < 5; j++)
                {
                    if(j < i-1)
                    {
                        System.out.printf(" ");
                    }
                    else
                    {
                        System.out.printf("*");
                    }
                }
                System.out.println();
            }
        }
    }
    
    public static void main(String args[])
    {
        Patterns.Pattern1 p1 = new Patterns.Pattern1();
        p1.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern2 p2 = new Patterns.Pattern2();
        p2.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern3 p3 = new Patterns.Pattern3();
        p3.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern4 p4 = new Patterns.Pattern4();
        p4.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern5 p5 = new Patterns.Pattern5();
        p5.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern6 p6 = new Patterns.Pattern6();
        p6.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern7 p7 = new Patterns.Pattern7();
        p7.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern8 p8 = new Patterns.Pattern8();
        p8.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern9 p9 = new Patterns.Pattern9();
        p9.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern10 p10 = new Patterns.Pattern10();
        p10.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern11 p11 = new Patterns.Pattern11();
        p11.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern12 p12 = new Patterns.Pattern12();
        p12.printPattern();

        System.out.println("--------------------------------");

        Patterns.Pattern13 p13 = new Patterns.Pattern13();
        p13.printPattern();

        System.out.println("--------------------------------");


    }
}