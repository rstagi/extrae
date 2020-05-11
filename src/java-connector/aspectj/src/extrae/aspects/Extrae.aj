package extrae.aspects;

import org.aspectj.lang.reflect.*;
import java.util.*;
import java.lang.*;

public aspect Extrae {

    private static HashMap<Integer, Integer> notifyingTasks = new HashMap();
    private static HashMap<Integer, List<Integer>> waitingTasks = new HashMap();

    pointcut   Tread_Create(): !within(extrae.aspects.Extrae) && call (* java.lang.Thread.start (..));
    before() : Tread_Create()
            {
                es.bsc.cepbatools.extrae.JavaProbes.ThreadStartBegin();
                es.bsc.cepbatools.extrae.Wrapper.SetNumTasks(es.bsc.cepbatools.extrae.Wrapper.GetNumTasks()+1);
            }

    after() returning () : Tread_Create()
            {
                es.bsc.cepbatools.extrae.JavaProbes.ThreadStartEnd();
            }

    pointcut    Notify(): !within(extrae.aspects.Extrae) && call (* java.lang.Object.notify (..));
    before() : Notify()
            {
                es.bsc.cepbatools.extrae.JavaProbes.ObjectNotifyBegin();

                Object calligObj = thisJoinPoint.getThis();
                Integer objID = Integer.valueOf(System.identityHashCode(calligObj));

                System.out.println("Notifying event on " + objID);

                List<Integer> waitingTskIDs = waitingTasks.get(objID);

                if (waitingTskIDs != null)
                {
                    for (Integer taskID : waitingTskIDs)
                    {
                        System.out.println("Detected waiting task with ID: " + taskID);
                        es.bsc.cepbatools.extrae.Wrapper.Comm(true, objID, 1, taskID, objID);
                    }

                    Integer myThreadID = es.bsc.cepbatools.extrae.Wrapper.GetTaskID();
                    Integer myTaskID = myThreadID-1;
                    es.bsc.cepbatools.extrae.Wrapper.SetTaskID(myTaskID);
                    notifyingTasks.put(objID, myTaskID);
                }
            }

    after() returning () : Notify()
            {
                es.bsc.cepbatools.extrae.JavaProbes.ObjectNotifyEnd();
            }
    
    pointcut    Wait(): !within(extrae.aspects.Extrae) && call (* java.lang.Object.wait (..));
    before() : Wait()
            {
                Object calligObj = thisJoinPoint.getThis();
                Integer objID = Integer.valueOf(System.identityHashCode(calligObj));
                Integer myThreadID = es.bsc.cepbatools.extrae.Wrapper.GetThreadID();
                Integer myTaskID = myThreadID-1;
                es.bsc.cepbatools.extrae.Wrapper.SetTaskID(myTaskID);

                System.out.println("Wait event start on Object " + objID);
                if (waitingTasks.get(objID)==null)
                {
                    System.out.println("Creating ArrayList inside waitingTasks");
                    waitingTasks.put(objID, new ArrayList());
                }

                waitingTasks.get(objID).add(myTaskID);
                System.out.println("Added task " + myTaskID + " to the waiting list for object " + objID);
            }
    
    after() returning () : Wait()
            {
                Object calligObj = thisJoinPoint.getThis();
                Integer objID = Integer.valueOf(System.identityHashCode(calligObj));

                System.out.println("Wait event on object " + objID + " finished.");
                Integer notifyerID = notifyingTasks.get(objID);
                if (notifyerID != null)
                {
                    System.out.println("Detected notifyer with ID " + notifyerID);
                    es.bsc.cepbatools.extrae.Wrapper.Comm(false, objID, 1, notifyerID, objID);
                }
                
                Integer myTaskID = Integer.valueOf(es.bsc.cepbatools.extrae.Wrapper.GetTaskID());
                System.out.println("Created communication event between notifyer " + notifyerID + " and receiver " + myTaskID);
                int index = waitingTasks.get(objID).indexOf(myTaskID);
                waitingTasks.get(objID).remove(index);
                if (waitingTasks.get(objID).size() == 0)
                {
                    System.out.println("Waiting tasks list is empty. Removing waiting and notifying tasks related to object " + objID);
                    waitingTasks.remove(objID);
                    notifyingTasks.remove(objID);
                }
            }

    /* main symbol instrumentation and adds symbolic information to the instrumented routines */
    pointcut main_execution(): execution ( public static void main (..));
    before (): main_execution()
            {
                /* es.bsc.cepbatools.extrae.Wrapper.Init(); not needed, auto instrumentation of main? */
            }


}
