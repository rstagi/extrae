package extrae.aspects;

import org.aspectj.lang.reflect.*;

public aspect Extrae {

    pointcut   Tread_Create(): !within(extrae.aspects.Extrae) && call (* java.lang.Thread.start (..));
    before(): Tread_Create()
            {
                es.bsc.cepbatools.extrae.Wrapper.Eventandcounters (48000007, 1);
            }

    after() returning () : Tread_Create()
            {
                es.bsc.cepbatools.extrae.Wrapper.Eventandcounters (48000007, 0);
            }

    /* main symbol instrumentation and adds symbolic information to the instrumented routines */
    pointcut main_execution(): execution ( public static void main (..));
    before (): main_execution()
            {
                /* es.bsc.cepbatools.extrae.Wrapper.Init(); not needed, auto instrumentation of main? */
            }


}
