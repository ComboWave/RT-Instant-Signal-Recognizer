TL:DR - Signal recognition using Arduino's and basic electronic components using the principles of Real time DSP

July 19,2021 Roy Ben Avraham


The idea of Real Time Instant Signal Recognizer (RTISR)
By using scalar product of two vector we can use two different arrays and compare between them by using normalised correlation (normalised cross correlation).

Be sure to understand why DC levelling is used, you may read it this article:

http://paulbourke.net/miscellaneous/correlate/

Basic RT Instant Recognizer works in the following way:

Known N-counts of a "Etalon Signal" are stored as 1D array in the program memory x[I].

(You may find it useful to learn how to store array in the FLASH memory of the Arduino:

https://www.arduino.cc/en/pmwiki.php?n=Reference/PROGMEM

Counts of an "Incoming Signal" are inputted into a Ring buffer of size N (stored in the default RAM memory) y[i] on timer interrupt, ISR calculated "r" - normalised correlation between "Etalon Signal" x[i] and "Incoming Signal".

![image](https://user-images.githubusercontent.com/105777016/169117436-dd0461b4-99d8-464a-b129-86a06677e350.png)

That is RT instant recognizer compares N last counts of the "Incoming Signal" x[i] with fixed N counts of the Etalon Signal y[i]. Be sure to understand how delay d and ring buffer indexing are related. And yes, a number of loops in the ISR.

Ok, so far was the demands from the system- Lets get to work!

I chose to sample at 20[Hz] frequency (due to the system's technical difficulties) and found that 5 samples will be enough in order to recognize the desired signal.

After the recognition of the signal, the system will no longer search for matches, also it is always possible to turn the switch and the system will re-search.

In addition, it is possible to change the desired frequency whenever one wants.

User Manual:
1) Choose a frequency to recognize (sin(8, 4, 5 Hz), sqr(8, 4 Hz), trg(8Hz)), using the signal-generator named “Input signal”.

Where:

Sin stands for sine wave with 8/4/5 [Hz] frequency.
sqr stands for square wave pulse with 8/4 [Hz] frequency.
Trg stands for triangle pulse with 8 [Hz] frequency.
2) Now, if a recognition was made – the system will print that the signal was recognized and in addition, the system will turn on a LED according to the letters number.

3) After the recognition was complete, you can press the button and the system will start to re-search a new frequency or you can change the input signals and noise.

Implementation of the RTISR:
In order to create the known signals, we wrote a function (“CreateEtalonArrays”) which calculates the signals according to their sampling frequency (in our case 20 [Hz]).

This frequency was chosen after several tests in higher frequencies. We have come to the conclusion that in our conditions this is a good trade-off between well working system and the efficiency with respect to time.

I chose 6 waves with those frequencies(changeable):

Sine wave with the following frequencies: 8, 4, 5 [Hz].

sqr wave with the following frequencies: 8, 4 [Hz].

And Triangular wave with the frequency of 8 [Hz].

The program will print an array which can be copied directly into the Arduino “progmem” memory.

(It is not possible to initialize the “progmem” while running the program)

The function calculates the averages of each signal as well (each signal in separate) which can also be stored in the “progmem”.

In order to achieve our samples we had to use the function generator, used an Arduino to sample 5 samples from each function.

In addition, the results were printed on the serial monitor, than we copied the data to the main program. (see below attachments)

![image](https://user-images.githubusercontent.com/105777016/169117605-c98ef02e-6cd7-4169-b66a-9d034d8461f8.png)
(Secondary circuit & program output)

A little explanation of Active mixer usage:
In this part, we used 741 op amplifier (non inverting summing amplifier)

As shown in the figure below:

![image](https://user-images.githubusercontent.com/105777016/169117785-e92b4e38-f325-44ef-a81f-ae1f16feb35a.png)
(Signal comes from the 3'd on left - yellow wire, Noise comes from 3 row on boton left - yellow wire and the mixed output is out of the blue wire on the 3'd row from right in the right top)

In order to differ between different signal it is possible to give each signal a different LED color.

![image](https://user-images.githubusercontent.com/105777016/169118025-9fb8f4ca-6968-466d-a82b-7e721cb7e33c.png)
(LEDS array)

Legend:

8 [Hz] sin – Orange LED

5 [Hz] sin – Green LED

4 [Hz] sin – Yellow LED

8 [Hz] sqr – Blue LED

4 [Hz] sqr – Red LED

8 [Hz] trg – White LED

Note:

Only one LED can be turned on at a time.

Some signals recognition results for motivation:
8 [Hz] sqr with 40 [Hz] sqr wave noise (0.5[v] Amplitude and 1[v] peak to peak):

![image](https://user-images.githubusercontent.com/105777016/169118115-83f19dd3-9bcb-46da-bc1b-b8694fe597b9.png)

4 [Hz] sin with 40 [Hz] sqr wave noise (0.5[v] Amplitude and 1[v] peak to peak):

![image](https://user-images.githubusercontent.com/105777016/169118149-85f00299-0f04-4bb4-a2a6-23466fcfcebf.png)

8 [Hz] trg with 40 [Hz] sin wave noise (0.5[v] Amplitude and 1[v] peak to peak):

![image](https://user-images.githubusercontent.com/105777016/169118183-b3a39b77-f8bf-45b7-88ac-c47bc74cc1bc.png)

Conclusions of mine after implementing this system (Check it out on your own!)
From the results we can conclude that the system can recognize quite easily the both rect waves for a large variants of amplitudes and voltage offsets.

The sin waves with the frequencies 5 Hz and 4 Hz both can be recognized without any problem but for a smaller variant of amplitudes and offset voltages.

However, The sin wave with the frequency of 8 Hz and the triangle wave with the frequency of 8 Hz both has a high sensitivity and low variant of offset voltages and amplitudes.

Note: A reliable test is when we succeeded to recognized the wave 4 times.

Features:
•the system can recognize 6 different signals:

•Sin 8[Hz].

•Sin 5[Hz].

•Sin 4[Hz].

•Rect 8[Hz].

•Rect 4[Hz].

•Triangle 8[Hz].

•The system can mix the input signals with a large variant of noises- 3 different waves and for each wave a large scale of frequencies.

•The system can recognize a wave even with a high noise (compared to the input wave, for a noise frequency that is two times larger than the input frequency).

•We can change the input signal we want to recognize without restarting the simulation.

System layout:
![image](https://user-images.githubusercontent.com/105777016/169118264-33f0119e-14e0-461f-807c-277dbab90779.png)

