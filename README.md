Этап 2.  
Пусть у функции root() погрешность вычисления корня (ROOTPRECISION) равна e1. Так как все три функции f1(x), f2(x) и f3(x) монотонны, то погрешность определенного интеграла функции fn() на отрезке между точек x1 и x2 (x1 < x2), вычисленных функцией root(), не превышает Qn&nbsp;=&nbsp;max(|T1|,&nbsp;|T2|), где:  
&nbsp;&nbsp;&nbsp;&nbsp;T1 = e1 * (max(|fn(x1)|, |fn(x1 - e1)|) + max(|fn(x2)|, |fn(x2 + e1)|),  
&nbsp;&nbsp;&nbsp;&nbsp;T2 = e1 * (max(|fn(x1)|, |fn(x1 + e1)|) + max(|fn(x2)|, |fn(x2 - e1)|)  
Так как функция integral обладает собственной точностью e2 (INTEGRALPRECISION), то итоговая погрешность (Rn) не превышает Qn&nbsp;+&nbsp;e2, т.е. Rn&nbsp;<=&nbsp;Qn&nbsp;+&nbsp;e2.  
Если точки x12, x23, x31 - точки пересечения функций с соотв. номерами, вычисленные функцией root(), то площадь ограниченной тремя функциями фигуры считается как:  
&nbsp;&nbsp;&nbsp;&nbsp;I&nbsp;=&nbsp;integral(f1,&nbsp;x31,&nbsp;x12)&nbsp;+&nbsp;integral(f2,&nbsp;x12,&nbsp;x23)&nbsp;+&nbsp;integral(f3,&nbsp;x23,&nbsp;x31)  
Значит итоговая погрешность для I не будет превышать e&nbsp;=&nbsp;R1&nbsp;+&nbsp;R2&nbsp;+&nbsp;R3&nbsp;=&nbsp;Q1&nbsp;+&nbsp;Q2&nbsp;+&nbsp;Q3&nbsp;+&nbsp;3*e2.  
В задании требуется соблюсти e&nbsp;<=&nbsp;0.0001:  
&nbsp;&nbsp;&nbsp;&nbsp;Для данных функций f1, f2 и f3, e1&nbsp;=&nbsp;e2&nbsp;=&nbsp;0.000005 дают требуемую погрешность e&nbsp;(e&nbsp;<&nbsp;0.000091). Возможны и другие комбинации e1 и e2, дающие подходящую   погрешность при меньших вычислительных затратах, однако я выбрал максимальные подходяшие e1&nbsp;=&nbsp;e2 с шагом 0.000001.
