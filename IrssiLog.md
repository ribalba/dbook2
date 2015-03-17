#The log from the IRC channel that concieved dbook2.

This is how libdbook2 was born. In the UNIX lab at Bournemouth Uni.

# Log #

```
17:44 -!- didi [n=didi@194.66.66.187] has joined #bunix
17:44 -!- Topic for #bunix: BUNIX HACKATHON!!! :: #bunix on irc.freenode.net
17:44 -!- Topic set by beamer [] [Sat Jun 13 17:43:01 2009]
17:44 [Users #bunix]
17:44 [@vext01] [ beamer] [ didi] 
17:44 -!- Irssi: #bunix: Total of 3 nicks [1 ops, 0 halfops, 0 voices, 2 normal]
17:44 -!- Channel #bunix created Sat Jun 13 17:39:05 2009
17:44 -!- Irssi: Join to #bunix was synced in 1 secs
17:44 -!- #bunix [freenode-info] help freenode weed out clonebots, please register your IRC nick and auto-identify: http://freenode.net/faq.shtml#nicksetup
17:44 < didi> HELLO
18:10  * vext01 starts research how to make shared libraries
18:23 < didi> got shared libs compiling 
18:26 <@vext01> How to make a shared library on UNIX:
18:26 <@vext01> make a C file with the functions you want to export inside, lets call ours libdbook.c
18:27 <@vext01> gcc -shared -o test.c
18:27 <@vext01> woops
18:27 <@vext01> that should be 'gcc -shared test.c'
18:27 <@vext01> this makes test.o
18:28 <@vext01> now do 'gcc -shared -o libdbook.so.0.1 test.o'
18:28 <@vext01> this makes the .so
18:28 <@vext01> beware version numbering!
18:29 <@vext01> you will probably need a header file so people dont need to prototype themsleves
18:32 <@vext01> remember when building use -L/path/to/where/lib/is -llibname
18:32 <@vext01> eg in my test i was able to call my test function like so:
18:32 <@vext01> cc -L. -ldbook test.c -o test
18:33 <@vext01> -L would not be needed if the lib is in the standard linker path
18:44  * vext01 looks at how to extend ruby
18:53 -!- darkphnx [n=Adium@194.66.66.126] has joined #bunix
18:56 -!- Diccon [n=diccon_t@194.80.66.116] has joined #bunix
18:57 -!- k3isen [n=k3isen@194.80.66.23] has joined #bunix
18:57 < k3isen> Sup Gs!!
18:58 < k3isen> k3isen@gmail.com
18:59 < didi> http://code.google.com/p/dbook2/source/browse/
18:59 < didi> http://code.google.com/p/dbook2/
19:19  * vext01 forgot to install ruby
19:21  * Diccon downloaded JDK6, which insisted on launching firefox?
19:29 < didi> HATES C
19:30 < didi> lib prototype should be finished in a few secs
19:43 < didi> and it is
19:44  * Diccon grabs C header file he needs
19:45 < Diccon> not quite sure what to do with it yet :D
19:45 <@vext01> writes test program
19:53 <@vext01> *
19:53 <@vext01>  * DBOOK2
19:53 <@vext01>  * $Id$
19:53 <@vext01>  * -----------------------
19:53 <@vext01>  * libdbook test stub
19:53 <@vext01>  */
19:58 -!- Diccon [n=diccon_t@194.80.66.116] has left #bunix []
19:58 -!- Diccon [n=diccon_t@194.80.66.116] has joined #bunix
19:59 < Diccon> didi is an arse
19:59 < darkphnx> hey, there's this really cool thing you can do with computers, just press alt+f4 to see
19:59 < Diccon> room empties
19:59 < Diccon> :D
20:15 <@vext01> sanitize v 1: make sanitary by cleaning or sterilizing [syn: sanitise, hygienize,
20:15 < didi> edd "Where has my code gone" count +1 (2)
20:17 <@vext01> x31% LD_LIBRARY_PATH=../src ./dbook-test
20:17 <@vext01> dbook_check_isbn()...
20:17 <@vext01> returned: 0
20:17 <@vext01> dbook_isbn_10_to_13()...
20:17 <@vext01> returned: 0
20:17 <@vext01> dbook_isbn_13_to_10()...
20:17 <@vext01> returned: 0
20:18 <@vext01> dbook_sanitize()...
20:18 <@vext01> returned: 0
20:18 <@vext01> dbook_get_isbn_details()...
20:18 <@vext01> returned: 0
20:18 <@vext01> dbook_configure()...
20:18 <@vext01> returned: 0
20:18 <@vext01> dbook_get_config()...
20:18 <@vext01> returned: 0
20:18 <@vext01> Tests complete...
20:22 <@vext01> (gdb) print b1
20:23 <@vext01> $2 = {isbn = "9780091906122",  title = "Are You a Geek?", '\0' <repeats 234 times>,  author = "Tim Collins", '\0' <repeats 238 times>,  date = "6-09-2005", '\0' <repeats 40 times>,  publisher = "Ebury Press", '\0' <repeats 238 times>, edition = 0,  pagecount = 0, image_pic = '\0' <repeats 249 times>,  category = '\0' <repeats 21 times>, "x", '\0' <repeats 12 times>
20:30 -!- k3isen [n=k3isen@194.80.66.23] has quit []
20:37 -!- vext01 changed the topic of #bunix to: BUNIX HACKATHON!!! :: #bunix on irc.freenode.net :: http://code.google.com/p/dbook2/source/checkout
20:56 <@vext01> FASCIASTS TO DATE: Apple, cygwin...
21:04 < didi> why does the lib stuff in Mac be so stupid
21:09 <@vext01> http://www.adp-gmbh.ch/cpp/gcc/create_lib.html
21:10 -!- k3isen [n=k3isen@194.80.66.23] has joined #bunix
21:11 <@vext01> http://www.adp-gmbh.ch/cpp/gcc/create_lib.html
21:11 < didi> figured out how to get shared libs working under mac
21:11 < didi> really simple
21:11 < didi> it is just totally different to anything else
21:13 -!- swissslinky [n=slinky@92-236-69-79.cable.ubr14.aztw.blueyonder.co.uk] has joined #bunix
21:14 < didi> hahah
21:14 < didi> you are missing a massive hack
21:14 < didi> MR swiss
21:14 < swissslinky> so, what have you come up with so far?
21:15 < didi> http://code.google.com/p/dbook2/
21:15 < didi> look at the source
21:15 < didi> and we are currently trying to port it to win and mac
21:16 < swissslinky> looking good
21:16 < Diccon> 9:15 and Dan realises subversion isnt installed lol
21:28 < Diccon> we've all given up with making librarys work on 4 different platforms (when 3 dont) cheating time!
21:32 < darkphnx> static ftw
21:33 <@vext01> (fake static at that)
21:57 <@vext01> x31% fortune -o
21:57 <@vext01> He who sneezes without a handkerchief takes matters into his own
21:57 <@vext01> hands.
22:00 < didi> backslash a rings a bell 
22:04 < darkphnx> brief comic interlude: http://bulapictures.com/index.php?l=show&id=130
22:04 < darkphnx> I especially like the guy with a pipe
22:08 < swissslinky> guy? GUY? That's the legend that is Bill Bailey!! 
22:08 < darkphnx> precisely :)
22:09 < Diccon> carefully laid trap there by Dan/Dark ;)
22:11 <@vext01> swissslinky: hey
22:18 < swissslinky> Hey Ed!!
22:22 <@vext01> hi hi
22:23 <@vext01> here in spirit
22:23 <@vext01> :)
22:23  * vext01 is playing with cmake as making shared libs portable is bloody hard
22:34 -!- swissslinky_ [n=slinky@92-236-69-79.cable.ubr14.aztw.blueyonder.co.uk] has joined #bunix
22:40 -!- swissslinky_ [n=slinky@92-236-69-79.cable.ubr14.aztw.blueyonder.co.uk] has left #bunix []
22:49 -!- swissslinky [n=slinky@92-236-69-79.cable.ubr14.aztw.blueyonder.co.uk] has quit [Read error: 110 (Connection timed out)]
23:31 < Diccon> grr compiling against JNLI c libs, but cantt find where java put them
23:48 < didi> pizza
23:49 <@vext01> didi == ETOOMANYFASCIASTS
23:52 <@vext01> % fortune -o
23:52 <@vext01> Communists do it without class.
00:06 <@vext01> cmake ++
00:06 <@vext01> \o/
00:06 < Diccon> sweet, cmake gets a 100% win, Ubuntu agrees
00:06 < k3isen> * g o a t s e x * g o a t s e x * g o a t s e x *
00:06 < k3isen> g                                               g  
00:06 < k3isen> o /     \             \            /    \       o
00:06 < k3isen> a|       |             \          |      |      a
00:06 < k3isen> t|       `.             |         |       :     t
00:06 < k3isen> s`        |             |        \|       |     s
00:06 < k3isen> e \       | /       /  \\\   --__ \\       :    e
00:06 < k3isen> x  \      \/   _--~~          ~--__| \     |    x  
00:07 < k3isen> *   \      \_-~                    ~-_\    |    *
00:07 < k3isen> g    \_     \        _.--------.______\|   |    g
00:07 < k3isen> o      \     \______// _ ___ _ (_(__>  \   |    o
00:07 < k3isen> a       \   .  C ___)  ______ (_(____>  |  /    a
00:07 < k3isen> t       /\ |   C ____)/      \ (_____>  |_/     t
00:07 < k3isen> s      / /\|   C_____)       |  (___>   /  \    s
00:07 < k3isen> e     |   (   _C_____)\______/  // _/ /     \   e
00:07 < k3isen> x     |    \  |__   \\_________// (__/       |  x
00:07 < k3isen> *    | \    \____)   `----   --'             |  *
00:07 < k3isen> g    |  \_          ___\       /_          _/ | g
00:07 < k3isen> o   |              /    |     |  \            | o
00:07 < k3isen> a   |             |    /       \  \           | a
00:07 < k3isen> t   |          / /    |         |  \           |t
00:07 < k3isen> s   |         / /      \__/\___/    |          |s
00:07 < k3isen> e  |           /        |    |       |         |e
00:07 < k3isen> x  |          |         |    |       |         |x
00:07 < k3isen> * g o a t s e x * g o a t s e x * g o a t s e x *
00:07 < Diccon> you absolute bastard
00:08 <@vext01>  /kick ^W^W^W^
00:16 -!- swissslinky [n=slinky@92-236-69-79.cable.ubr14.aztw.blueyonder.co.uk] has joined #bunix
00:18 < swissslinky> I see you've been busy
00:25 < didi> ohh yes
00:27 < Diccon> Doxygen is the weapon of choice
00:29 < didi> someone might want to create a doxy file
00:29 < didi> for all the projects
00:29 < didi> some tool on ubuntu should be able to do that for you
00:29 < didi> with a funky gui
00:30 < Diccon> I'll look at that when ive got a woking Java test app calling C
00:35 < darkphnx> python module compiles, loads, dies horribly
00:53 < didi> isbn check for isbn10 works
00:56 < didi>  ______  ______   _____   _____  _     _ |     \ |_____] |     | |     | |____/  |_____/ |_____] |_____| |_____| |    \_
00:57 -!- Irssi: Pasting 11 lines to #bunix. Press Ctrl-K if you wish to do this or Ctrl-C to cancel.
00:57 < didi>                                  ___           ___           ___     
00:57 < didi>      _____         _____         /\  \         /\  \         /|  |    
00:57 < didi>     /::\  \       /::\  \       /::\  \       /::\  \       |:|  |    
00:57 < didi>    /:/\:\  \     /:/\:\  \     /:/\:\  \     /:/\:\  \      |:|  |    
00:57 < didi>   /:/  \:\__\   /:/ /::\__\   /:/  \:\  \   /:/  \:\  \   __|:|  |    
00:57 < didi>  /:/__/ \:|__| /:/_/:/\:|__| /:/__/ \:\__\ /:/__/ \:\__\ /\ |:|__|____
00:57 < didi>  \:\  \ /:/  / \:\/:/ /:/  / \:\  \ /:/  / \:\  \ /:/  / \:\/:::::/__/
00:57 < didi>   \:\  /:/  /   \::/_/:/  /   \:\  /:/  /   \:\  /:/  /   \::/~~/~    
00:57 < didi>    \:\/:/  /     \:\/:/  /     \:\/:/  /     \:\/:/  /     \:\~~\     
00:57 < didi>     \::/  /       \::/  /       \::/  /       \::/  /       \:\__\    
00:57 < didi>      \/__/         \/__/         \/__/         \/__/         \/__/    
01:00 -!- swissslinky [n=slinky@92-236-69-79.cable.ubr14.aztw.blueyonder.co.uk] has quit []
01:15 < darkphnx> ATTENTION FELLOW HACKATHONERS - we now have a basic, working python wrapper
01:24 <@vext01> :)
01:26 < darkphnx> CMake Warning (dev) in CMakeLists.txt:
01:26 < darkphnx>   No cmake_minimum_required command is present.  A line of code such as
01:26 < darkphnx>     cmake_minimum_required(VERSION 2.6)
01:26 < darkphnx>   should be added at the top of the file.  The version specified may be lower
01:26 < darkphnx>   if you wish to support older CMake versions for this project.  For more
01:26 < darkphnx>   information run "cmake --help-policy CMP0000".
01:26 < darkphnx> This warning is for project developers.  Use -Wno-dev to suppress it.
01:27 < Diccon> Ok, basic, corrrectly named Java->C wrapper
01:49 <@vext01> http://fukung.net/v/2905/lilaaah.jpg
01:49 <@vext01> fukung for the win
01:53 < Diccon> make for java lib made, doing make clean
01:58 < Diccon> Commited correct named Java class and C wrapper lib also Make file
01:58 < Diccon> whoo, compiles links and runs basic C functiton from Java!
02:20 < darkphnx> my kingdom for an associative array
02:24 < Diccon> Henry VI would be proud
02:42 < k3isen> #include "Logic.h"
02:42 < k3isen> Logic::Logic(){}
02:42 < k3isen> Logic::~Logic(){}
02:42 < k3isen> void Logic::run()
02:42 < k3isen> {
02:42 -!- k3isen [n=k3isen@194.80.66.23] has quit [Excess Flood]
02:42 -!- k3isen [n=k3isen@194.80.66.23] has joined #bunix
04:23 <@vext01> http://stackoverflow.com/questions/992068/building-a-python-shared-object-binding-with-cmake-which-depends-upon-external-l
04:23 < didi> the sun is rising
04:24 <@vext01> so is the oracle :)
04:32 < didi> http://wiki.cacr.caltech.edu/danse/index.php/Compiling_the_Numbers_example_under_Linux
04:33 < darkphnx> dan@daedalus-ubuntu:~/src/dbook2/dbookpy$ gcc -I/usr/include/python2.6 -I../libdbook/src/ -c dbookpy.c 
04:33 < darkphnx> dan@daedalus-ubuntu:~/src/dbook2/dbookpy$ gcc ../libdbook/src/libdbook.o dbookpy.o -fpic -shared -o dbookpy.so
04:35 <@vext01> >>> dbook.check_isbn("4782646")
04:35 <@vext01> It seams the ISBN passed in is neither a valid 10 or 13zsh: segmentation fault (core dumped)  python
04:36 < darkphnx> 0330267388
04:36 <@vext01> >>> import dbook
04:36 <@vext01> >>> dbook.check_isbn("0330267388")
04:36 <@vext01> It seams the ISBN passed in is neither a valid 10 or 131
04:36 <@vext01> zsh: segmentation fault (core dumped)  python
04:39 <@vext01> ^ = http://fukung.net/v/1463/315461288_7866a07739_o.jpg
04:40 <@vext01> >>> import dbook
04:40 <@vext01> python:./dbook.so: undefined symbol 'PyInt_AsInt'
04:40 <@vext01> python:./dbook.so: undefined symbol 'PyInt_AsInt'
04:40 <@vext01> Traceback (most recent call last): File "<stdin>", line 1, in <module>
04:40 <@vext01> ImportError: Cannot load specified object
04:54 <@vext01> dan and d off home
04:54 <@vext01> time 4:48
04:54 <@vext01> (am)
04:55 -!- darkphnx [n=Adium@194.66.66.126] has left #bunix []
04:58  * vext01 calling it a day also
04:59 -!- vext01 [n=edd@194.80.66.189] has quit ["leaving"]
```