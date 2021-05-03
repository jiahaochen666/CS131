<p align="center" style="text-align:center"><b><span lang="IT" style="font-size:
14.0pt;mso-ansi-language:IT">LAB <span class="GramE">2:&nbsp; MPI</span> (C++)</span></b></p>
<p style="text-align:justify"><b style="mso-bidi-font-weight:normal">NOTE</b><span style="mso-bidi-font-weight:bold">: Skeletons will be provided for Part B </span><b style="mso-bidi-font-weight:normal">only</b><span style="mso-bidi-font-weight:
bold">. Data files will be provided for all problems.<o:p></o:p></span></p>
<p style="text-align:justify"><b style="mso-bidi-font-weight:normal">NOTE</b><span style="mso-bidi-font-weight:bold">: Use </span><span class="SpellE"><b style="mso-bidi-font-weight:normal">MPI_Scatter</b></span><span style="mso-bidi-font-weight:bold"> to distribute the data.<span style="mso-spacerun:yes">&nbsp;&nbsp; </span><o:p></o:p></span></p>
<p style="text-align:justify"><b><span style="font-size:12.0pt">Part A (An
image histogram using <i>Tarry’s algorithm</i>):<o:p></o:p></span></b></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">You are
given two matrices, D and A. D is a grayscale image with 8-bit pixels (0-255).
A is a matrix describing the DS connectivity (an adjacency bit matrix). Row <span class="SpellE"><i style="mso-bidi-font-style:normal">i</i></span> in the matrix A
describes nodes that node <span class="SpellE"><i style="mso-bidi-font-style:
normal">i</i></span> is connected to (a 1 in position A[<span class="SpellE"><span class="GramE">i,j</span></span>] means node j have a direct, bidirectional link).
A node can send messages <u>only</u> to its neighbors (as per the adjacency
matrix). Assume that otherwise it does not know how many nodes are in the
system.<span style="mso-spacerun:yes">&nbsp; </span><o:p></o:p></span></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">You are
given two matrices, D and A. D is a grayscale image with 8-bit pixels (0-255).
A is a matrix describing the DS connectivity (an adjacency bit matrix). Row <span class="SpellE"><i style="mso-bidi-font-style:normal">i</i></span> in the matrix A
describes nodes that node <span class="SpellE"><i style="mso-bidi-font-style:
normal">i</i></span> is connected to (a 1 in position A[<span class="SpellE"><span class="GramE">i,j</span></span>] means node j have a direct, bidirectional link).
A node can send messages <u>only</u> to its neighbors (as per the adjacency
matrix). Assume that otherwise it does not know how many nodes are in the
system.<span style="mso-spacerun:yes">&nbsp; </span><o:p></o:p></span></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">Your
implementation will take </span><b style="mso-bidi-font-weight:normal">three</b><span style="mso-bidi-font-weight:bold"> command line arguments (in this order):
Grayscale PGM image, path to text file with the adjacency matrix and output
file name. <o:p></o:p></span></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">Use the
same grayscale PGM images from Lab 1. You can use the code from those labs to
read an image into the matrix D.<o:p></o:p></span></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">A sample
text file with an adjacency matrix with 4 nodes will look as follows:<o:p></o:p></span></p>
<table class="MsoTableGrid" border="0" cellspacing="0" cellpadding="0" style="border-collapse:collapse;border:none;mso-yfti-tbllook:1184;mso-padding-alt:
 0in 5.4pt 0in 5.4pt;mso-border-insideh:none;mso-border-insidev:none">
 <tbody><tr style="mso-yfti-irow:0;mso-yfti-firstrow:yes;height:14.25pt">
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:1;height:15.1pt">
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:15.1pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:15.1pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:15.1pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:15.1pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:2;height:14.25pt">
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
 </tr>
 <tr style="mso-yfti-irow:3;mso-yfti-lastrow:yes;height:14.25pt">
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">1<o:p></o:p></span></p>
  </td>
  <td width="24" valign="top" style="width:17.95pt;padding:0in 5.4pt 0in 5.4pt;
  height:14.25pt">
  <p style="text-align:justify"><span style="mso-bidi-font-weight:bold">0<o:p></o:p></span></p>
  </td>
 </tr>
</tbody></table>
<p style="text-align:justify"><span style="color:white;mso-color-alt:windowtext;
mso-bidi-font-weight:bold"><span style="mso-spacerun:yes">&nbsp;</span>It shows that
Node 1 is connected to 2 and 4, Node 2 is connected to 1 and 3, Node 3 is
connected to 2 and 4, and Node 4 is connected to 1 and 3.</span><span style="mso-bidi-font-weight:bold"><o:p></o:p></span></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">A histogram
calculates the number of pixels that have the same intensity, <span class="GramE">e.g.</span> the same pixel value, for every pixel value between 0
and 255.<o:p></o:p></span></p>
<p style="text-align:justify"><span style="mso-bidi-font-weight:bold">Print
histogram output into the output file where each line will represent the # of
pixels for each intensity. Therefore, the output file MUST have 256 lines only.
<u>Use the initiator node (node 2) to print the output file, </u>once the algorithm
ends, i.e., the token returns to the initiator node.<o:p></o:p></span></p>
<p class="MsoNormal" style="background:white"><b><span style="font-size:12.0pt;
font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;"><o:p>&nbsp;</o:p></span></b></p>
<p class="MsoNormal" style="background:white"><b><span style="font-size:12.0pt;
font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;;
color:black;mso-color-alt:windowtext">Tarry’s Algorithm:</span></b><b><span style="font-size:12.0pt;font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:
&quot;Times New Roman&quot;"><o:p></o:p></span></b></p>
<p class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
background:white"><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:
&quot;Times New Roman&quot;;color:#004959">Assumption: </span><span style="font-family:
&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;;color:black;
mso-color-alt:windowtext"><span style="mso-spacerun:yes">&nbsp;</span>An </span><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;;
color:#BF003F">undirected </span><span style="font-family:&quot;Times New Roman&quot;,serif;
mso-fareast-font-family:&quot;Times New Roman&quot;;color:black;mso-color-alt:windowtext">network
of processes. </span><span style="font-family:&quot;Times New Roman&quot;,serif;
mso-fareast-font-family:&quot;Times New Roman&quot;"><o:p></o:p></span></p>
<p class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
background:white"><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:
&quot;Times New Roman&quot;;color:#181717;mso-themecolor:background2;mso-themeshade:26;
mso-style-textfill-fill-color:#181717;mso-style-textfill-fill-themecolor:background2;
mso-style-textfill-fill-alpha:100.0%;mso-style-textfill-fill-colortransforms:
lumm=10000">The algorithm performs a complete network traversal visiting each
node once and returning the result (token) to the initiator.<o:p></o:p></span></p>
<p class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
background:white"><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:
&quot;Times New Roman&quot;;color:black;mso-color-alt:windowtext">An initiator starts by
sending out a token to its neighbors.<span style="mso-spacerun:yes">&nbsp; </span>A
parent of a process is another process from which it first received a token.</span><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;"><o:p></o:p></span></p>
<ul type="disc">
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l2 level1 lfo5;tab-stops:list .5in;background:white"><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;;
     color:#BF003F">Rule 1: </span><span style="font-family:&quot;Times New Roman&quot;,serif;
     mso-fareast-font-family:&quot;Times New Roman&quot;;color:black;mso-color-alt:windowtext">A
     process never forwards the token through the same channel twice. </span><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;"><o:p></o:p></span></li>
 <li class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
     mso-list:l2 level1 lfo5;tab-stops:list .5in;background:white"><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;;
     color:#BF003F">Rule 2: </span><span style="font-family:&quot;Times New Roman&quot;,serif;
     mso-fareast-font-family:&quot;Times New Roman&quot;;color:black;mso-color-alt:windowtext">A
     process only forwards the token to its parent when there is no other
     option (<span class="GramE">i.e.</span> no other link to send it on to)</span><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:&quot;Times New Roman&quot;"><o:p></o:p></span></li>
</ul>
<p class="MsoNormal" style="mso-margin-top-alt:auto;mso-margin-bottom-alt:auto;
margin-left:.5in;background:white"><span style="font-family:&quot;Times New Roman&quot;,serif;
mso-fareast-font-family:&quot;Times New Roman&quot;;color:black;mso-color-alt:windowtext">The
token travels through each channel both ways, and finally ends up at the
initiator. </span><span style="font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:
&quot;Times New Roman&quot;"><o:p></o:p></span></p>
<p style="text-align:justify"><b><span style="font-size:12.0pt">Part B1 (Word
Frequency: Reduction):<o:p></o:p></span></b></p>
<p>Implement a simple and parallel version of an algorithm to count the word
frequency using MPI.<span style="mso-spacerun:yes">&nbsp; </span>To aggregate your
results in the Master process you must use <span class="SpellE">MPI_Reduce</span>.</p>
<p class="MsoNormal"><span style="font-family:Monaco;mso-fareast-font-family:
&quot;Times New Roman&quot;;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black">int&nbsp;<span class="SpellE">MPI_<span class="GramE">Reduce</span></span><span class="GramE">(</span>const&nbsp;void
*<span class="SpellE">sendbuf</span>, void
*recvbuf,&nbsp;int&nbsp;count,&nbsp;MPI_Datatype&nbsp;datatype,&nbsp;MPI_Op&nbsp;op,&nbsp;int&nbsp;root,&nbsp;MPI_Comm&nbsp;comm)</span><span style="font-size:12.0pt;font-family:&quot;Times New Roman&quot;,serif;mso-fareast-font-family:
&quot;Times New Roman&quot;"><o:p></o:p></span></p>
<p><b><span style="font-size:12.0pt"><o:p>&nbsp;</o:p></span></b></p>
<p><b><span style="font-size:12.0pt">Part B2 (Word Frequency: Ring topology): </span></b><b style="mso-bidi-font-weight:normal"><o:p></o:p></b></p>
<p>Use the same implementation of the algorithm as PartB1 but instead of using <span class="SpellE">MPI_reduce</span>, pass the partial result between the tasks as
messages. You will use a point-to-point communication between “adjacent” tasks,
<span class="GramE">e.g.</span> <span class="SpellE">i</span> and i-1.</p>
<p>Look at the provided skeleton for CL <span class="SpellE">args</span> and for
choosing between part B1 and B2.</p>
<p><b><span style="font-size:12.0pt">Timing (Part B1 and B2): <o:p></o:p></span></b></p>
<p style="text-align:justify">Report the timings for Part B1 and B2 with 2, 4,
8, and 16 processes. Be careful when timing your code, you want to time only the
processing time, not reading the input. Only the Master process should time the
execution, not the worker threads. Create a graph from that timing data and
explain what they show. </p>
<p style="text-align:justify">Also explain:</p>
<p style="margin-left:.5in;text-align:justify;text-indent:-.25in;mso-list:l0 level1 lfo2"><!--[if !supportLists]--><span style="mso-fareast-font-family:Times;mso-bidi-font-family:Times"><span style="mso-list:Ignore">1.<span style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
</span></span></span><!--[endif]-->What is the topology used by MPI to implements
its Reduce?</p>
<p style="margin-left:.5in;text-align:justify;text-indent:-.25in;mso-list:l0 level1 lfo2"><!--[if !supportLists]--><span style="mso-fareast-font-family:Times;mso-bidi-font-family:Times"><span style="mso-list:Ignore">2.<span style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
</span></span></span><!--[endif]-->How does the ring topology affect the runtime?</p>
<p style="margin-left:.5in;text-align:justify;text-indent:-.25in;mso-list:l0 level1 lfo2"><!--[if !supportLists]--><span style="mso-fareast-font-family:Times;mso-bidi-font-family:Times"><span style="mso-list:Ignore">3.<span style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
</span></span></span><!--[endif]-->Is there a case where the ring topology may be
faster?<span style="mso-spacerun:yes">&nbsp; </span></p>
<p style="margin-left:.5in;text-align:justify;text-indent:-.25in;mso-list:l0 level1 lfo2"><!--[if !supportLists]--><span style="mso-fareast-font-family:Times;mso-bidi-font-family:Times"><span style="mso-list:Ignore">4.<span style="font:7.0pt &quot;Times New Roman&quot;">&nbsp;&nbsp;&nbsp;&nbsp;
</span></span></span><!--[endif]-->How many messages are passed between machines
when program is run with 2, 4, 8, and 16 processes?</p>
<p style="text-align:justify">See below for the submission instructions. How to
time the implementation will be discussed in the discussion.</p>
<p style="text-align:justify"><b style="mso-bidi-font-weight:normal">NOTE</b>:
See the <b>MPI How-To</b> guide on the assignment web page before running your
implementations on <span class="SpellE">openlab</span> servers.</p>
<p style="text-align:justify"><b>Submit via Canvas:&nbsp; </b><i>YOU<b> MUST</b>
USE the file names below</i></p>
<p style="text-align:justify">1.<span style="font-size:7.0pt;font-family:&quot;Times New Roman&quot;,serif">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span>Implementation of your C++ program: <b style="mso-bidi-font-weight:normal">ImplementationA.cpp</b>
and <b style="mso-bidi-font-weight:normal">ImplementationB.cpp </b>(includes
both B1 and B2)</p>
<p style="text-align:justify">2.<span style="font-size:7.0pt;font-family:&quot;Times New Roman&quot;,serif">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
</span>Analysis of the timing for Part B1 and B2: <b style="mso-bidi-font-weight:
normal">Timing.pdf</b> </p>
<p style="text-align:justify"><b>Point Breakdown:</b></p>
<p style="text-align:justify">Part A: Implementation -&gt; 40pts</p>
<p style="text-align:justify">Part B1 and B2: Implementation&nbsp;-&gt; 50pts
(25pts each), Timing -&gt; 10pts</p>
<p style="text-align:justify"><b>USEFUL LINKS:</b> </p>
<p style="text-align:justify"><a href="https://computing.llnl.gov/tutorials/mpi">MPI
Tutorial </a>&nbsp;&nbsp; </p>
<p style="text-align:justify"><b>NOTE:</b> The TA cannot solve the exercises
for you, but he can answer your questions!</p>
<p style="text-align:justify"><span style="font-family:&quot;Times New Roman&quot;,serif"><o:p>&nbsp;</o:p></span></p>
