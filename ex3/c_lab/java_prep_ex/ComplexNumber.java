public class ComplexNumber{
    private double real, img;
    private final double EPSILON = 0.001;
    
    public ComplexNumber(double my_real, double my_img){
        real = my_real;
        img = my_img;
    }
    
    
    public double getRealPart()
    {
        return real;
    }
    
    public double getImaginaryPart()
    {
        return img;
    }
    
    public ComplexNumber plus(ComplexNumber other)
    {
        double new_real = real + other.getRealPart();
        double new_img = img + other.getImaginaryPart();
        ComplexNumber c_new = new ComplexNumber(new_real,new_img);
        return c_new;
    }
    
    public ComplexNumber minus(ComplexNumber other)
    {
        double new_real = real - other.getRealPart();
        double new_img = img - other.getImaginaryPart();
        ComplexNumber c_new = new ComplexNumber(new_real,new_img);
        return c_new;
    }
    
    public ComplexNumber times(ComplexNumber other)
    {
        double new_real = real*other.getRealPart() - img*other.getImaginaryPart();
        double new_img = real*other.getImaginaryPart() + img*other.getRealPart();
        ComplexNumber c_new = new ComplexNumber(new_real,new_img);
        return c_new;
    }
    
    
    public ComplexNumber reciprocal() 
    {
        double scale = real*real + img*img;
        ComplexNumber c_new = new ComplexNumber(real / scale, -img / scale);
        return  c_new;
    }
    
    public ComplexNumber divide(ComplexNumber other)
    {
        ComplexNumber c = this;
        ComplexNumber c_new = c.times(other.reciprocal());
        return c_new;
    }
    
    public double getRadius()
    {
        return Math.sqrt(real*real + img*img);
    }
    
    public double getArgument()
    {
        return Math.atan2(img, real);
    }
    
    public boolean almostEquals(ComplexNumber other)
    {
        ComplexNumber c = this;
        ComplexNumber difference = c.minus(other);
        double length = Math.abs(difference.getRadius());
        if(length < EPSILON)
        {
            return true;
        }
        return false;
    }
    
}
