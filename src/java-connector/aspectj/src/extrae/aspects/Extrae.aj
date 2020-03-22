package extrae.aspects;

import org.aspectj.lang.reflect.*;
import java.util.*;

public aspect Extrae {

    private static HashMap<Integer, Integer> notifyingThreads = new HashMap();
    private static HashMap<Integer, List<Integer>> waitingThreads = new HashMap();

    pointcut   Tread_Create(): !within(extrae.aspects.Extrae) && call (* java.lang.Thread.start (..));
    before() : Tread_Create()
            {
                es.bsc.cepbatools.extrae.JavaProbes.ThreadStartBegin();
            }

    after() returning () : Tread_Create()
            {
                es.bsc.cepbatools.extrae.JavaProbes.ThreadStartEnd();
            }

    pointcut    Notify(): !within(extrae.aspects.Extrae) && call (* java.lang.Object.notify (..));
    before() : Notify()
            {
                //es.bsc.cepbatools.extrae.JavaProbes.ObjectNotifyBegin();

                Object calligObj = thisJoinPoint.getThis();
                Integer objID = Integer.valueOf(System.identityHashCode(calligObj));

                List<Integer> waitingThdIDs = waitingThreads.get(objID);

                if (waitingThdIDs != null)
                {
                    for (Integer threadID : waitingThdIDs)
                    {
                        es.bsc.cepbatools.extrae.Wrapper.Comm(true, objID, 1, threadID, objID);
                    }

                    Integer myThreadID = es.bsc.cepbatools.extrae.Wrapper.GetThreadID();
                    notifyingThreads.put(objID, myThreadID);
                }
            }

    after() returning () : Notify()
            {
                //es.bsc.cepbatools.extrae.JavaProbes.ObjectNotifyEnd();
            }
    
    pointcut    Wait(): !within(extrae.aspects.Extrae) && call (* java.lang.Object.wait (..));
    before() : Wait()
            {
                Object calligObj = thisJoinPoint.getThis();
                Integer objID = Integer.valueOf(System.identityHashCode(calligObj));
                Integer myThreadID = es.bsc.cepbatools.extrae.Wrapper.GetThreadID();
                
                if (waitingThreads.get(objID)==null)
                {
                    waitingThreads.put(objID, new ArrayList());
                }

                waitingThreads.get(objID).add(myThreadID);
            }
    
    after() returning () : Wait()
            {
                Object calligObj = thisJoinPoint.getThis();
                Integer objID = Integer.valueOf(System.identityHashCode(calligObj));

                Integer notifyerID = notifyingThreads.get(objID);
                if (notifyerID != null)
                {
                    es.bsc.cepbatools.extrae.Wrapper.Comm(false, objID, 1, notifyerID, objID);
                }
                
                Integer myThreadID = Integer.valueOf(es.bsc.cepbatools.extrae.Wrapper.GetThreadID());
                int index = waitingThreads.get(objID).indexOf(myThreadID);
                waitingThreads.get(objID).remove(index);
                if (waitingThreads.get(objID).size() == 0)
                {
                    waitingThreads.remove(objID);
                    notifyingThreads.remove(objID);
                }
            }

    /* main symbol instrumentation and adds symbolic information to the instrumented routines */
    pointcut main_execution(): execution ( public static void main (..));
    before (): main_execution()
            {
                /* es.bsc.cepbatools.extrae.Wrapper.Init(); not needed, auto instrumentation of main? */
            }


}
