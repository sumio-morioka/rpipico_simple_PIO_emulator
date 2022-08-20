/////////////////////////////////////////////////////////////////////////////////////////
// An Easy-to-Use RPI Pico PIO Emulator
// ORIGINAL FILE: https://github.com/sumio-morioka/rpipico_simple_PIO_emulator/picopio_emu.h
// Japanese explanation: Sep. 2022 issue of the Interface Magazine, CQ Publishing Co.Ltd. (https://interface.cqpub.co.jp/)
// 
// Main code
// 
// History:
// (1) Original coding by Sumio Morioka									2022.08.20
//		(CONTACT: Facebook sumio.morioka  e-mail morioka@fb3.so-net.ne.jp)
// 
/////////////////////////////////////////////////////////////////////////////////////////


//                    GNU GENERAL PUBLIC LICENSE
//                       Version 3, 29 June 2007
//
// Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
// Everyone is permitted to copy and distribute verbatim copies
// of this license document, but changing it is not allowed.
//
//                            Preamble
//
//  The GNU General Public License is a free, copyleft license for
//software and other kinds of works.
//
//  The licenses for most software and other practical works are designed
//to take away your freedom to share and change the works.  By contrast,
//the GNU General Public License is intended to guarantee your freedom to
//share and change all versions of a program--to make sure it remains free
//software for all its users.  We, the Free Software Foundation, use the
//GNU General Public License for most of our software; it applies also to
//any other work released this way by its authors.  You can apply it to
//your programs, too.
//
//  When we speak of free software, we are referring to freedom, not
//price.  Our General Public Licenses are designed to make sure that you
//have the freedom to distribute copies of free software (and charge for
//them if you wish), that you receive source code or can get it if you
//want it, that you can change the software or use pieces of it in new
//free programs, and that you know you can do these things.
//
//  To protect your rights, we need to prevent others from denying you
//these rights or asking you to surrender the rights.  Therefore, you have
//certain responsibilities if you distribute copies of the software, or if
//you modify it: responsibilities to respect the freedom of others.
//
//  For example, if you distribute copies of such a program, whether
//gratis or for a fee, you must pass on to the recipients the same
//freedoms that you received.  You must make sure that they, too, receive
//or can get the source code.  And you must show them these terms so they
//know their rights.
//
//  Developers that use the GNU GPL protect your rights with two steps:
//(1) assert copyright on the software, and (2) offer you this License
//giving you legal permission to copy, distribute and/or modify it.
//
//  For the developers' and authors' protection, the GPL clearly explains
//that there is no warranty for this free software.  For both users' and
//authors' sake, the GPL requires that modified versions be marked as
//changed, so that their problems will not be attributed erroneously to
//authors of previous versions.
//
//  Some devices are designed to deny users access to install or run
//modified versions of the software inside them, although the manufacturer
//can do so.  This is fundamentally incompatible with the aim of
//protecting users' freedom to change the software.  The systematic
//pattern of such abuse occurs in the area of products for individuals to
//use, which is precisely where it is most unacceptable.  Therefore, we
//have designed this version of the GPL to prohibit the practice for those
//products.  If such problems arise substantially in other domains, we
//stand ready to extend this provision to those domains in future versions
//of the GPL, as needed to protect the freedom of users.
//
//  Finally, every program is threatened constantly by software patents.
//States should not allow patents to restrict development and use of
//software on general-purpose computers, but in those that do, we wish to
//avoid the special danger that patents applied to a free program could
//make it effectively proprietary.  To prevent this, the GPL assures that
//patents cannot be used to render the program non-free.
//
//  The precise terms and conditions for copying, distribution and
//modification follow.
//
//                       TERMS AND CONDITIONS
//
//  0. Definitions.
//
//  "This License" refers to version 3 of the GNU General Public License.
//
//  "Copyright" also means copyright-like laws that apply to other kinds of
//works, such as semiconductor masks.
//
//  "The Program" refers to any copyrightable work licensed under this
//License.  Each licensee is addressed as "you".  "Licensees" and
//"recipients" may be individuals or organizations.
//
//  To "modify" a work means to copy from or adapt all or part of the work
//in a fashion requiring copyright permission, other than the making of an
//exact copy.  The resulting work is called a "modified version" of the
//earlier work or a work "based on" the earlier work.
//
//  A "covered work" means either the unmodified Program or a work based
//on the Program.
//
//  To "propagate" a work means to do anything with it that, without
//permission, would make you directly or secondarily liable for
//infringement under applicable copyright law, except executing it on a
//computer or modifying a private copy.  Propagation includes copying,
//distribution (with or without modification), making available to the
//public, and in some countries other activities as well.
//
//  To "convey" a work means any kind of propagation that enables other
//parties to make or receive copies.  Mere interaction with a user through
//a computer network, with no transfer of a copy, is not conveying.
//
//  An interactive user interface displays "Appropriate Legal Notices"
//to the extent that it includes a convenient and prominently visible
//feature that (1) displays an appropriate copyright notice, and (2)
//tells the user that there is no warranty for the work (except to the
//extent that warranties are provided), that licensees may convey the
//work under this License, and how to view a copy of this License.  If
//the interface presents a list of user commands or options, such as a
//menu, a prominent item in the list meets this criterion.
//
//  1. Source Code.
//
//  The "source code" for a work means the preferred form of the work
//for making modifications to it.  "Object code" means any non-source
//form of a work.
//
//  A "Standard Interface" means an interface that either is an official
//standard defined by a recognized standards body, or, in the case of
//interfaces specified for a particular programming language, one that
//is widely used among developers working in that language.
//
//  The "System Libraries" of an executable work include anything, other
//than the work as a whole, that (a) is included in the normal form of
//packaging a Major Component, but which is not part of that Major
//Component, and (b) serves only to enable use of the work with that
//Major Component, or to implement a Standard Interface for which an
//implementation is available to the public in source code form.  A
//"Major Component", in this context, means a major essential component
//(kernel, window system, and so on) of the specific operating system
//(if any) on which the executable work runs, or a compiler used to
//produce the work, or an object code interpreter used to run it.
//
//  The "Corresponding Source" for a work in object code form means all
//the source code needed to generate, install, and (for an executable
//work) run the object code and to modify the work, including scripts to
//control those activities.  However, it does not include the work's
//System Libraries, or general-purpose tools or generally available free
//programs which are used unmodified in performing those activities but
//which are not part of the work.  For example, Corresponding Source
//includes interface definition files associated with source files for
//the work, and the source code for shared libraries and dynamically
//linked subprograms that the work is specifically designed to require,
//such as by intimate data communication or control flow between those
//subprograms and other parts of the work.
//
//  The Corresponding Source need not include anything that users
//can regenerate automatically from other parts of the Corresponding
//Source.
//
//  The Corresponding Source for a work in source code form is that
//same work.
//
//  2. Basic Permissions.
//
//  All rights granted under this License are granted for the term of
//copyright on the Program, and are irrevocable provided the stated
//conditions are met.  This License explicitly affirms your unlimited
//permission to run the unmodified Program.  The output from running a
//covered work is covered by this License only if the output, given its
//content, constitutes a covered work.  This License acknowledges your
//rights of fair use or other equivalent, as provided by copyright law.
//
//  You may make, run and propagate covered works that you do not
//convey, without conditions so long as your license otherwise remains
//in force.  You may convey covered works to others for the sole purpose
//of having them make modifications exclusively for you, or provide you
//with facilities for running those works, provided that you comply with
//the terms of this License in conveying all material for which you do
//not control copyright.  Those thus making or running the covered works
//for you must do so exclusively on your behalf, under your direction
//and control, on terms that prohibit them from making any copies of
//your copyrighted material outside their relationship with you.
//
//  Conveying under any other circumstances is permitted solely under
//the conditions stated below.  Sublicensing is not allowed; section 10
//makes it unnecessary.
//
//  3. Protecting Users' Legal Rights From Anti-Circumvention Law.
//
//  No covered work shall be deemed part of an effective technological
//measure under any applicable law fulfilling obligations under article
//11 of the WIPO copyright treaty adopted on 20 December 1996, or
//similar laws prohibiting or restricting circumvention of such
//measures.
//
//  When you convey a covered work, you waive any legal power to forbid
//circumvention of technological measures to the extent such circumvention
//is effected by exercising rights under this License with respect to
//the covered work, and you disclaim any intention to limit operation or
//modification of the work as a means of enforcing, against the work's
//users, your or third parties' legal rights to forbid circumvention of
//technological measures.
//
//  4. Conveying Verbatim Copies.
//
//  You may convey verbatim copies of the Program's source code as you
//receive it, in any medium, provided that you conspicuously and
//appropriately publish on each copy an appropriate copyright notice;
//keep intact all notices stating that this License and any
//non-permissive terms added in accord with section 7 apply to the code;
//keep intact all notices of the absence of any warranty; and give all
//recipients a copy of this License along with the Program.
//
//  You may charge any price or no price for each copy that you convey,
//and you may offer support or warranty protection for a fee.
//
//  5. Conveying Modified Source Versions.
//
//  You may convey a work based on the Program, or the modifications to
//produce it from the Program, in the form of source code under the
//terms of section 4, provided that you also meet all of these conditions:
//
//    a) The work must carry prominent notices stating that you modified
//    it, and giving a relevant date.
//
//    b) The work must carry prominent notices stating that it is
//    released under this License and any conditions added under section
//    7.  This requirement modifies the requirement in section 4 to
//    "keep intact all notices".
//
//    c) You must license the entire work, as a whole, under this
//    License to anyone who comes into possession of a copy.  This
//    License will therefore apply, along with any applicable section 7
//    additional terms, to the whole of the work, and all its parts,
//    regardless of how they are packaged.  This License gives no
//    permission to license the work in any other way, but it does not
//    invalidate such permission if you have separately received it.
//
//    d) If the work has interactive user interfaces, each must display
//    Appropriate Legal Notices; however, if the Program has interactive
//    interfaces that do not display Appropriate Legal Notices, your
//    work need not make them do so.
//
//  A compilation of a covered work with other separate and independent
//works, which are not by their nature extensions of the covered work,
//and which are not combined with it such as to form a larger program,
//in or on a volume of a storage or distribution medium, is called an
//"aggregate" if the compilation and its resulting copyright are not
//used to limit the access or legal rights of the compilation's users
//beyond what the individual works permit.  Inclusion of a covered work
//in an aggregate does not cause this License to apply to the other
//parts of the aggregate.
//
//  6. Conveying Non-Source Forms.
//
//  You may convey a covered work in object code form under the terms
//of sections 4 and 5, provided that you also convey the
//machine-readable Corresponding Source under the terms of this License,
//in one of these ways:
//
//    a) Convey the object code in, or embodied in, a physical product
//    (including a physical distribution medium), accompanied by the
//    Corresponding Source fixed on a durable physical medium
//    customarily used for software interchange.
//
//    b) Convey the object code in, or embodied in, a physical product
//    (including a physical distribution medium), accompanied by a
//    written offer, valid for at least three years and valid for as
//    long as you offer spare parts or customer support for that product
//    model, to give anyone who possesses the object code either (1) a
//    copy of the Corresponding Source for all the software in the
//    product that is covered by this License, on a durable physical
//    medium customarily used for software interchange, for a price no
//    more than your reasonable cost of physically performing this
//    conveying of source, or (2) access to copy the
//    Corresponding Source from a network server at no charge.
//
//    c) Convey individual copies of the object code with a copy of the
//    written offer to provide the Corresponding Source.  This
//    alternative is allowed only occasionally and noncommercially, and
//    only if you received the object code with such an offer, in accord
//    with subsection 6b.
//
//    d) Convey the object code by offering access from a designated
//    place (gratis or for a charge), and offer equivalent access to the
//    Corresponding Source in the same way through the same place at no
//    further charge.  You need not require recipients to copy the
//    Corresponding Source along with the object code.  If the place to
//    copy the object code is a network server, the Corresponding Source
//    may be on a different server (operated by you or a third party)
//    that supports equivalent copying facilities, provided you maintain
//    clear directions next to the object code saying where to find the
//    Corresponding Source.  Regardless of what server hosts the
//    Corresponding Source, you remain obligated to ensure that it is
//    available for as long as needed to satisfy these requirements.
//
//    e) Convey the object code using peer-to-peer transmission, provided
//    you inform other peers where the object code and Corresponding
//    Source of the work are being offered to the general public at no
//    charge under subsection 6d.
//
//  A separable portion of the object code, whose source code is excluded
//from the Corresponding Source as a System Library, need not be
//included in conveying the object code work.
//
//  A "User Product" is either (1) a "consumer product", which means any
//tangible personal property which is normally used for personal, family,
//or household purposes, or (2) anything designed or sold for incorporation
//into a dwelling.  In determining whether a product is a consumer product,
//doubtful cases shall be resolved in favor of coverage.  For a particular
//product received by a particular user, "normally used" refers to a
//typical or common use of that class of product, regardless of the status
//of the particular user or of the way in which the particular user
//actually uses, or expects or is expected to use, the product.  A product
//is a consumer product regardless of whether the product has substantial
//commercial, industrial or non-consumer uses, unless such uses represent
//the only significant mode of use of the product.
//
//  "Installation Information" for a User Product means any methods,
//procedures, authorization keys, or other information required to install
//and execute modified versions of a covered work in that User Product from
//a modified version of its Corresponding Source.  The information must
//suffice to ensure that the continued functioning of the modified object
//code is in no case prevented or interfered with solely because
//modification has been made.
//
//  If you convey an object code work under this section in, or with, or
//specifically for use in, a User Product, and the conveying occurs as
//part of a transaction in which the right of possession and use of the
//User Product is transferred to the recipient in perpetuity or for a
//fixed term (regardless of how the transaction is characterized), the
//Corresponding Source conveyed under this section must be accompanied
//by the Installation Information.  But this requirement does not apply
//if neither you nor any third party retains the ability to install
//modified object code on the User Product (for example, the work has
//been installed in ROM).
//
//  The requirement to provide Installation Information does not include a
//requirement to continue to provide support service, warranty, or updates
//for a work that has been modified or installed by the recipient, or for
//the User Product in which it has been modified or installed.  Access to a
//network may be denied when the modification itself materially and
//adversely affects the operation of the network or violates the rules and
//protocols for communication across the network.
//
//  Corresponding Source conveyed, and Installation Information provided,
//in accord with this section must be in a format that is publicly
//documented (and with an implementation available to the public in
//source code form), and must require no special password or key for
//unpacking, reading or copying.
//
//  7. Additional Terms.
//
//  "Additional permissions" are terms that supplement the terms of this
//License by making exceptions from one or more of its conditions.
//Additional permissions that are applicable to the entire Program shall
//be treated as though they were included in this License, to the extent
//that they are valid under applicable law.  If additional permissions
//apply only to part of the Program, that part may be used separately
//under those permissions, but the entire Program remains governed by
//this License without regard to the additional permissions.
//
//  When you convey a copy of a covered work, you may at your option
//remove any additional permissions from that copy, or from any part of
//it.  (Additional permissions may be written to require their own
//removal in certain cases when you modify the work.)  You may place
//additional permissions on material, added by you to a covered work,
//for which you have or can give appropriate copyright permission.
//
//  Notwithstanding any other provision of this License, for material you
//add to a covered work, you may (if authorized by the copyright holders of
//that material) supplement the terms of this License with terms:
//
//    a) Disclaiming warranty or limiting liability differently from the
//    terms of sections 15 and 16 of this License; or
//
//    b) Requiring preservation of specified reasonable legal notices or
//    author attributions in that material or in the Appropriate Legal
//    Notices displayed by works containing it; or
//
//    c) Prohibiting misrepresentation of the origin of that material, or
//    requiring that modified versions of such material be marked in
//    reasonable ways as different from the original version; or
//
//    d) Limiting the use for publicity purposes of names of licensors or
//    authors of the material; or
//
//    e) Declining to grant rights under trademark law for use of some
//    trade names, trademarks, or service marks; or
//
//    f) Requiring indemnification of licensors and authors of that
//    material by anyone who conveys the material (or modified versions of
//    it) with contractual assumptions of liability to the recipient, for
//    any liability that these contractual assumptions directly impose on
//    those licensors and authors.
//
//  All other non-permissive additional terms are considered "further
//restrictions" within the meaning of section 10.  If the Program as you
//received it, or any part of it, contains a notice stating that it is
//governed by this License along with a term that is a further
//restriction, you may remove that term.  If a license document contains
//a further restriction but permits relicensing or conveying under this
//License, you may add to a covered work material governed by the terms
//of that license document, provided that the further restriction does
//not survive such relicensing or conveying.
//
//  If you add terms to a covered work in accord with this section, you
//must place, in the relevant source files, a statement of the
//additional terms that apply to those files, or a notice indicating
//where to find the applicable terms.
//
//  Additional terms, permissive or non-permissive, may be stated in the
//form of a separately written license, or stated as exceptions;
//the above requirements apply either way.
//
//  8. Termination.
//
//  You may not propagate or modify a covered work except as expressly
//provided under this License.  Any attempt otherwise to propagate or
//modify it is void, and will automatically terminate your rights under
//this License (including any patent licenses granted under the third
//paragraph of section 11).
//
//  However, if you cease all violation of this License, then your
//license from a particular copyright holder is reinstated (a)
//provisionally, unless and until the copyright holder explicitly and
//finally terminates your license, and (b) permanently, if the copyright
//holder fails to notify you of the violation by some reasonable means
//prior to 60 days after the cessation.
//
//  Moreover, your license from a particular copyright holder is
//reinstated permanently if the copyright holder notifies you of the
//violation by some reasonable means, this is the first time you have
//received notice of violation of this License (for any work) from that
//copyright holder, and you cure the violation prior to 30 days after
//your receipt of the notice.
//
//  Termination of your rights under this section does not terminate the
//licenses of parties who have received copies or rights from you under
//this License.  If your rights have been terminated and not permanently
//reinstated, you do not qualify to receive new licenses for the same
//material under section 10.
//
//  9. Acceptance Not Required for Having Copies.
//
//  You are not required to accept this License in order to receive or
//run a copy of the Program.  Ancillary propagation of a covered work
//occurring solely as a consequence of using peer-to-peer transmission
//to receive a copy likewise does not require acceptance.  However,
//nothing other than this License grants you permission to propagate or
//modify any covered work.  These actions infringe copyright if you do
//not accept this License.  Therefore, by modifying or propagating a
//covered work, you indicate your acceptance of this License to do so.
//
//  10. Automatic Licensing of Downstream Recipients.
//
//  Each time you convey a covered work, the recipient automatically
//receives a license from the original licensors, to run, modify and
//propagate that work, subject to this License.  You are not responsible
//for enforcing compliance by third parties with this License.
//
//  An "entity transaction" is a transaction transferring control of an
//organization, or substantially all assets of one, or subdividing an
//organization, or merging organizations.  If propagation of a covered
//work results from an entity transaction, each party to that
//transaction who receives a copy of the work also receives whatever
//licenses to the work the party's predecessor in interest had or could
//give under the previous paragraph, plus a right to possession of the
//Corresponding Source of the work from the predecessor in interest, if
//the predecessor has it or can get it with reasonable efforts.
//
//  You may not impose any further restrictions on the exercise of the
//rights granted or affirmed under this License.  For example, you may
//not impose a license fee, royalty, or other charge for exercise of
//rights granted under this License, and you may not initiate litigation
//(including a cross-claim or counterclaim in a lawsuit) alleging that
//any patent claim is infringed by making, using, selling, offering for
//sale, or importing the Program or any portion of it.
//
//  11. Patents.
//
//  A "contributor" is a copyright holder who authorizes use under this
//License of the Program or a work on which the Program is based.  The
//work thus licensed is called the contributor's "contributor version".
//
//  A contributor's "essential patent claims" are all patent claims
//owned or controlled by the contributor, whether already acquired or
//hereafter acquired, that would be infringed by some manner, permitted
//by this License, of making, using, or selling its contributor version,
//but do not include claims that would be infringed only as a
//consequence of further modification of the contributor version.  For
//purposes of this definition, "control" includes the right to grant
//patent sublicenses in a manner consistent with the requirements of
//this License.
//
//  Each contributor grants you a non-exclusive, worldwide, royalty-free
//patent license under the contributor's essential patent claims, to
//make, use, sell, offer for sale, import and otherwise run, modify and
//propagate the contents of its contributor version.
//
//  In the following three paragraphs, a "patent license" is any express
//agreement or commitment, however denominated, not to enforce a patent
//(such as an express permission to practice a patent or covenant not to
//sue for patent infringement).  To "grant" such a patent license to a
//party means to make such an agreement or commitment not to enforce a
//patent against the party.
//
//  If you convey a covered work, knowingly relying on a patent license,
//and the Corresponding Source of the work is not available for anyone
//to copy, free of charge and under the terms of this License, through a
//publicly available network server or other readily accessible means,
//then you must either (1) cause the Corresponding Source to be so
//available, or (2) arrange to deprive yourself of the benefit of the
//patent license for this particular work, or (3) arrange, in a manner
//consistent with the requirements of this License, to extend the patent
//license to downstream recipients.  "Knowingly relying" means you have
//actual knowledge that, but for the patent license, your conveying the
//covered work in a country, or your recipient's use of the covered work
//in a country, would infringe one or more identifiable patents in that
//country that you have reason to believe are valid.
//
//  If, pursuant to or in connection with a single transaction or
//arrangement, you convey, or propagate by procuring conveyance of, a
//covered work, and grant a patent license to some of the parties
//receiving the covered work authorizing them to use, propagate, modify
//or convey a specific copy of the covered work, then the patent license
//you grant is automatically extended to all recipients of the covered
//work and works based on it.
//
//  A patent license is "discriminatory" if it does not include within
//the scope of its coverage, prohibits the exercise of, or is
//conditioned on the non-exercise of one or more of the rights that are
//specifically granted under this License.  You may not convey a covered
//work if you are a party to an arrangement with a third party that is
//in the business of distributing software, under which you make payment
//to the third party based on the extent of your activity of conveying
//the work, and under which the third party grants, to any of the
//parties who would receive the covered work from you, a discriminatory
//patent license (a) in connection with copies of the covered work
//conveyed by you (or copies made from those copies), or (b) primarily
//for and in connection with specific products or compilations that
//contain the covered work, unless you entered into that arrangement,
//or that patent license was granted, prior to 28 March 2007.
//
//  Nothing in this License shall be construed as excluding or limiting
//any implied license or other defenses to infringement that may
//otherwise be available to you under applicable patent law.
//
//  12. No Surrender of Others' Freedom.
//
//  If conditions are imposed on you (whether by court order, agreement or
//otherwise) that contradict the conditions of this License, they do not
//excuse you from the conditions of this License.  If you cannot convey a
//covered work so as to satisfy simultaneously your obligations under this
//License and any other pertinent obligations, then as a consequence you may
//not convey it at all.  For example, if you agree to terms that obligate you
//to collect a royalty for further conveying from those to whom you convey
//the Program, the only way you could satisfy both those terms and this
//License would be to refrain entirely from conveying the Program.
//
//  13. Use with the GNU Affero General Public License.
//
//  Notwithstanding any other provision of this License, you have
//permission to link or combine any covered work with a work licensed
//under version 3 of the GNU Affero General Public License into a single
//combined work, and to convey the resulting work.  The terms of this
//License will continue to apply to the part which is the covered work,
//but the special requirements of the GNU Affero General Public License,
//section 13, concerning interaction through a network will apply to the
//combination as such.
//
//  14. Revised Versions of this License.
//
//  The Free Software Foundation may publish revised and/or new versions of
//the GNU General Public License from time to time.  Such new versions will
//be similar in spirit to the present version, but may differ in detail to
//address new problems or concerns.
//
//  Each version is given a distinguishing version number.  If the
//Program specifies that a certain numbered version of the GNU General
//Public License "or any later version" applies to it, you have the
//option of following the terms and conditions either of that numbered
//version or of any later version published by the Free Software
//Foundation.  If the Program does not specify a version number of the
//GNU General Public License, you may choose any version ever published
//by the Free Software Foundation.
//
//  If the Program specifies that a proxy can decide which future
//versions of the GNU General Public License can be used, that proxy's
//public statement of acceptance of a version permanently authorizes you
//to choose that version for the Program.
//
//  Later license versions may give you additional or different
//permissions.  However, no additional obligations are imposed on any
//author or copyright holder as a result of your choosing to follow a
//later version.
//
//  15. Disclaimer of Warranty.
//
//  THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
//APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
//HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
//OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
//IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
//ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
//
//  16. Limitation of Liability.
//
//  IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
//WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS
//THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY
//GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE
//USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF
//DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD
//PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS),
//EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF
//SUCH DAMAGES.
//
//  17. Interpretation of Sections 15 and 16.
//
//  If the disclaimer of warranty and limitation of liability provided
//above cannot be given local legal effect according to their terms,
//reviewing courts shall apply local law that most closely approximates
//an absolute waiver of all civil liability in connection with the
//Program, unless a warranty or assumption of liability accompanies a
//copy of the Program in return for a fee.
//
//                     END OF TERMS AND CONDITIONS
//
//            How to Apply These Terms to Your New Programs
//
//  If you develop a new program, and you want it to be of the greatest
//possible use to the public, the best way to achieve this is to make it
//free software which everyone can redistribute and change under these terms.
//
//  To do so, attach the following notices to the program.  It is safest
//to attach them to the start of each source file to most effectively
//state the exclusion of warranty; and each file should have at least
//the "copyright" line and a pointer to where the full notice is found.
//
//    <one line to give the program's name and a brief idea of what it does.>
//    Copyright (C) <year>  <name of author>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//Also add information on how to contact you by electronic and paper mail.
//
//  If the program does terminal interaction, make it output a short
//notice like this when it starts in an interactive mode:
//
//    <program>  Copyright (C) <year>  <name of author>
//    This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//    This is free software, and you are welcome to redistribute it
//    under certain conditions; type `show c' for details.
//
//The hypothetical commands `show w' and `show c' should show the appropriate
//parts of the General Public License.  Of course, your program's commands
//might be different; for a GUI interface, you would use an "about box".
//
//  You should also get your employer (if you work as a programmer) or school,
//if any, to sign a "copyright disclaimer" for the program, if necessary.
//For more information on this, and how to apply and follow the GNU GPL, see
//<https://www.gnu.org/licenses/>.
//
//  The GNU General Public License does not permit incorporating your program
//into proprietary programs.  If your program is a subroutine library, you
//may consider it more useful to permit linking proprietary applications with
//the library.  If this is what you want to do, use the GNU Lesser General
//Public License instead of this License.  But first, please read
//<https://www.gnu.org/licenses/why-not-lgpl.html>.


#ifndef PICOPIO_EMU
#define PICOPIO_EMU

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

////////////////////////////
// emulator API
////////////////////////////
extern void pio_code_start(
	char	*funcname, 
	int		sm_id,					// state machine ID (for IRQ rel)

	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt, 

	bool	isr_shift_right, 		// SHIFTCTRL_IN_SHITDIR
	bool	isr_autopush,
	int		isr_autopush_threshold,	// SHIFTCTRL_PUSH_THRESH
	bool	osr_shift_right, 		// SHIFTCTRL_OUT_SHIFTDIR
	bool	osr_autopull,
	int		osr_autopull_threshold,	// SHIFTCTRL_PULL_THRESH
	int		jmp_pin,				// EXECCTRL_JMP_PIN
	bool	mov_status_sel,			// EXECCTRL_STATUS_SEL
	int		mov_status_val			// EXECCTRL_STATUS_SEL
);

extern void pio_code_start_simple(
	char	*funcname, 
	int		sm_id,					// state machine ID (will be used for IRQ rel)

	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt
);

extern void pio_code_end(bool write_code, char *file_name_code);

extern void pio_run_emulation(int cycles, char *file_name_in, char *file_name_out);

////////////////////////////
// instructions
////////////////////////////
extern void pio_jmp(int cond, char *lbl, int sideset, int delay);
extern void pio_wait(bool polarity, int src, int index, bool rel, int sideset, int delay);
extern void pio_in(int src, int bitcount, int sideset, int delay);
extern void pio_out(int dest, int bitcount, int sideset, int delay);
extern void pio_push(bool iffull, bool block, int sideset, int delay);
extern void pio_pull(bool ifempty, bool block, int sideset, int delay);
extern void pio_mov(int dest, int op, int src, int sideset, int delay);
extern void pio_irq(bool clr, bool wait, int index, bool rel, int sideset, int delay);
extern void pio_set(int dest, int data, int sideset, int delay);

// (pseudo instructions)
extern void pio_comment(char *string);		// max len = MAX_COMMENT_LEN
extern void pio_label(char *lbl);
extern void pio_nop(int sideset, int delay);
extern void pio_wrap_target(void);
extern void pio_wrap(void);
extern void pio_origin(int addr);

////////////////////////////
// constants
////////////////////////////

#define	PIO_UNUSE				-1

// instructions
#define	PIO_INST_IN				0
#define	PIO_INST_IRQ			1
#define	PIO_INST_JMP			2
#define	PIO_INST_MOV			3
#define	PIO_INST_OUT			4
#define	PIO_INST_PULL			5
#define	PIO_INST_PUSH			6
#define	PIO_INST_SET			7
#define	PIO_INST_WAIT			8

#define	PIO_INST_COMMENT		9
#define	PIO_INST_LABEL			10
#define	PIO_INST_NOP			11
#define	PIO_INST_WRAP_TARGET	12
#define	PIO_INST_WRAP			13
#define	PIO_INST_ORIGIN			14

// operands (in, out, mov)
#define	PIO_PINS				100
#define	PIO_X					101
#define	PIO_Y					102
#define	PIO_NULL				103
#define	PIO_ISR					104
#define	PIO_OSR					105
#define	PIO_PC					106
#define	PIO_EXEC				107
#define	PIO_PINDIRS				108
#define	PIO_STATUS				109

#define	PIO_NONE				200
#define	PIO_INVERT				201
#define	PIO_BIT_REVERSE			202

// operands (jmp)
#define	PIO_ALWAYS				300
#define	PIO_X_EQ_0				301
#define	PIO_X_NEQ_0_DEC			302
#define	PIO_Y_EQ_0				303
#define	PIO_Y_NEQ_0_DEC			304
#define	PIO_X_NEQ_Y				305
#define	PIO_PIN					306
#define	PIO_OSRE_NOTEMPTY		307

// operands (wait)
#define	PIO_GPIO				400
//#define	PIO_PIN				401		// defined above
#define	PIO_IRQ					402

// oprands (push, pull)
#define	PIO_BLOCK				500
#define	PIO_NOBLOCK				501


////////////////////////////
// other parameters
////////////////////////////
#define	PIO_MAX_FUNCNAME_LEN	256

#define	PIO_MAX_ASMLINE_LEN		1024
#define	PIO_MAX_ASMLINE_NUM		1024
#define	PIO_MAX_CSVLINE_LEN		1024

#define	PIO_MAX_INST_NUM		32		// don't change


/////////////////////////////////////////////////////////////////////////////////////////
// type definitions & global variables
/////////////////////////////////////////////////////////////////////////////////////////

typedef struct _pio_inst_list {
	bool		used;
	int			code_line;
	uint8_t		addr;			// 0-31

	int			inst_type;
	int			operand1;
	int			operand2;
	int			operand3;
	int			operand4;
	int			operand5;
	int			sideset;
	int			delay;

	char		strbuf[PIO_MAX_ASMLINE_LEN + 1];	// label or comment
	char		asmbuf[PIO_MAX_ASMLINE_LEN + 1];	// assembler output
} _PIO_INST;


typedef struct _pio_csvin_info {
	int			cycles;
	uint32_t	gpio_i;
	uint8_t		irq_i;
	bool		txfifo_push;
	uint32_t	txfifo_val;
	bool		rxfifo_pop;
} _PIO_CSVIN;


typedef struct _pio_global_info {
	// func name
	char		func_name[PIO_MAX_FUNCNAME_LEN];
	int			sm_id;

	// instruction
	_PIO_INST	asmline[PIO_MAX_ASMLINE_NUM];
	int			asmline_ptr;

	int			origin;
	int			inst_ptr;

	// CPU registers
	int			delay_timer;
	uint32_t	x;
	uint32_t	y;

	uint32_t	isr;
	int			isr_bitctr;
	uint32_t	osr;
	int			osr_bitctr;

	uint32_t	txfifo[4];
	int			txfifo_num;

	uint32_t	rxfifo[4];
	int			rxfifo_num;

	uint32_t	gpio_i;
	uint32_t	gpio_o;
	uint32_t	sideset_val;

	uint8_t		irq_i;
	uint8_t		irq_o;
	bool		irq_stalling;

	// emulator info (configuration values)
	// CPU I/O
	int			cycles;

	int			in_pins;
	int			in_num;
	int			out_pins;
	int			out_num;
	int			sideset_pins;
	int			sideset_num;
	bool		sideset_opt;
	int			sideset_maxval;
	int			delay_maxval;

	uint32_t	in_pin_setmask;
	uint32_t	out_pin_setmask;
	uint32_t	sideset_pin_setmask;
	uint32_t	jmp_pin_setmask;

	uint32_t	in_pin_clrmask;
	uint32_t	out_pin_clrmask;
	uint32_t	sideset_pin_clrmask;

	bool		isr_shift_right;
	bool		isr_autopush;
	int			isr_autopush_threshold;
	bool		osr_shift_right;
	bool		osr_autopull;
	int			osr_autopull_threshold;
	int			jmp_pin;
	bool		mov_status_sel;
	int			mov_status_val;

	int			wrap_target_line;
	int			wrap_line;

	FILE		*fin;
	FILE		*fout;
	FILE		*fcode;

	char		csvin_cache[PIO_MAX_CSVLINE_LEN];
	bool		csvin_cache_valid;
	_PIO_CSVIN	csvin_info;
} _PIO_INFO;


// global
static _PIO_INFO		_pio_info_g;

#define	PIO_SIMSTATE_CODE_START		0
#define	PIO_SIMSTATE_CODE_END		1
#define	PIO_SIMSTATE_RUN_START		2
#define	PIO_SIMSTATE_RUN_END		3

static int			_pio_emu_state_g	= PIO_SIMSTATE_CODE_START;

/////////////////////////////////////////////////////////////////////////////////////////
// function body
/////////////////////////////////////////////////////////////////////////////////////////

static uint32_t pio_maxval(unsigned int bitnum)
{
	// return (2^bitnum)-1
	uint32_t		mask;
	unsigned int	i;
	for (i = 0, mask = 0; i <= 32; i++) {
		if (i == bitnum)
			return mask;
		mask	= (mask << 1) | 1;
	}
	return	mask;
}


static unsigned int pio_bitnum(uint32_t val)
{
	uint32_t		mask;
	unsigned int	i;
	for (i = 0, mask = 1; i < 32; i++, mask <<= 1) {
		if (val < mask)
			return i;
	}
	return 32;
}


static uint32_t _pio_bitreverse(uint32_t val)
{
	uint32_t		ret;
	unsigned int	i;
	for (i = 0, ret = 0; i < 32; i++) {
		ret	<<= 1;
		if ((val & 1) != 0) {
			ret	|= 1;
		}
		val	>>= 1;
	}
	return ret;
}


void pio_code_start(
	char	*funcname, 
	int		sm_id,					// state machine ID (will be used for IRQ rel)

	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt, 

	bool	isr_shift_right, 		// SHIFTCTRL_IN_SHITDIR
	bool	isr_autopush,
	int		isr_autopush_threshold,	// SHIFTCTRL_PUSH_THRESH
	bool	osr_shift_right, 		// SHIFTCTRL_OUT_SHIFTDIR
	bool	osr_autopull,
	int		osr_autopull_threshold,	// SHIFTCTRL_PULL_THRESH
	int		jmp_pin,				// EXECCTRL_JMP_PIN
	bool	mov_status_sel,			// EXECCTRL_STATUS_SEL
	int		mov_status_val			// EXECCTRL_STATUS_SEL
)
{
	int	i;
	int delay_bitnum;

	if (_pio_emu_state_g != PIO_SIMSTATE_CODE_START) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal code-start position.\n");
		exit(1);
	}
	_pio_emu_state_g	= PIO_SIMSTATE_CODE_END;

	// initialize global info
	strcpy(_pio_info_g.func_name, funcname);			// NOTE: init value

	// state machine ID (for IRQ rel)
	if (sm_id < 0 || sm_id > 3) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal state machine id (0-3).\n");
		exit(1);
	}
	_pio_info_g.sm_id	= sm_id;

	// init internal info
	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*p;
		p						= &(_pio_info_g.asmline[i]);
		p->used					= false;
		p->code_line			= 0;
		p->addr					= 0;
		p->inst_type			= PIO_UNUSE;
		p->operand1				= PIO_UNUSE;
		p->operand2				= PIO_UNUSE;
		p->operand3				= PIO_UNUSE;
		p->operand4				= PIO_UNUSE;
		p->operand5				= PIO_UNUSE;
		p->sideset				= PIO_UNUSE;
		p->delay				= PIO_UNUSE;
		(p->strbuf)[0]			= '\0';
		(p->asmbuf)[0]			= '\0';
	}
	_pio_info_g.asmline_ptr		= 0;

	_pio_info_g.origin			= PIO_UNUSE;
	_pio_info_g.inst_ptr		= 0;

	_pio_info_g.delay_timer		= PIO_UNUSE;
	_pio_info_g.x				= 0;
	_pio_info_g.y				= 0;

	_pio_info_g.isr				= 0;
	_pio_info_g.osr				= 0;

	for (i = 0; i < 4; i++) {
		(_pio_info_g.txfifo)[i]	= 0;
	}
	_pio_info_g.txfifo_num		= 0;
	for (i = 0; i < 4; i++) {
		(_pio_info_g.rxfifo)[i]	= 0;
	}
	_pio_info_g.rxfifo_num		= 0;

	_pio_info_g.in_pins			= in_pins;			// NOTE: init value
	_pio_info_g.in_num			= in_num;			// NOTE: init value
	_pio_info_g.out_pins		= out_pins;			// NOTE: init value
	_pio_info_g.out_num			= out_num;			// NOTE: init value
	_pio_info_g.sideset_pins	= sideset_pins;		// NOTE: init value
	_pio_info_g.sideset_num		= sideset_num;		// NOTE: init value
	_pio_info_g.sideset_opt		= sideset_opt;		// NOTE: init value

	{
		if (in_pins == PIO_UNUSE || in_num == PIO_UNUSE) {
			in_pins			= 0;
			in_num			= 0;
		}
		if (out_pins == PIO_UNUSE || out_num == PIO_UNUSE) {
			out_pins		= 0;
			out_num			= 0;
		}
		if (sideset_pins == PIO_UNUSE || sideset_num == PIO_UNUSE) {
			sideset_pins	= 0;
			sideset_num		= 0;
		}

		// check pin assign
		if (in_pins < 0 || in_num < 0 || (in_pins + in_num) > 29) {		// 29 ... GPIO 0-28
			fprintf(stderr, "pio_code_start(): ERROR. Illegal number of input pins.\n");
			exit(1);
		}
		if (out_pins < 0 || out_num < 0 || (out_pins + out_num) > 29) {
			fprintf(stderr, "pio_code_start(): ERROR. Illegal number of output pins.\n");
			exit(1);
		}
		if (sideset_pins < 0 || sideset_num < 0 || (sideset_pins + sideset_num) > 29) {
			fprintf(stderr, "pio_code_start(): ERROR. Illegal number of sideset pins.\n");
			exit(1);
		}

		_pio_info_g.in_pin_setmask		= (pio_maxval(in_num)      << in_pins)      & 0x1FFFFFFF;	// 0x1FFFFFFF ... GPIO28-0
		_pio_info_g.out_pin_setmask		= (pio_maxval(out_num)     << out_pins)     & 0x1FFFFFFF;
		_pio_info_g.sideset_pin_setmask	= (pio_maxval(sideset_num) << sideset_pins) & 0x1FFFFFFF;

		_pio_info_g.in_pin_clrmask		= 0xFFFFFFFF ^ _pio_info_g.in_pin_setmask;					// (inversion)
		_pio_info_g.out_pin_clrmask		= 0xFFFFFFFF ^ _pio_info_g.out_pin_setmask;
		_pio_info_g.sideset_pin_clrmask	= 0xFFFFFFFF ^ _pio_info_g.sideset_pin_setmask;

//fprintf(stderr, "in mask   %08x\n", _pio_info_g.in_pin_setmask);
//fprintf(stderr, "out mask  %08x\n", _pio_info_g.out_pin_setmask);
//fprintf(stderr, "side mask %08x\n", _pio_info_g.sideset_pin_setmask);

		if ((_pio_info_g.in_pin_setmask & _pio_info_g.out_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Pin assignment overlap between input and output.\n");
			exit(1);
		}
		if ((_pio_info_g.in_pin_setmask & _pio_info_g.sideset_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Pin assignment overlap between input and sideset.\n");
			exit(1);
		}
		if ((_pio_info_g.out_pin_setmask & _pio_info_g.sideset_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Pin assignment overlap between output and sideet.\n");
			exit(1);
		}
	}

	_pio_info_g.gpio_i			= 0;
	_pio_info_g.gpio_o			= 0;
	_pio_info_g.sideset_val		= 0;

	_pio_info_g.irq_i			= 0;
	_pio_info_g.irq_o			= 0;
	_pio_info_g.irq_stalling	= false;

	_pio_info_g.cycles			= 1;
	_pio_info_g.isr_shift_right	= isr_shift_right;	// NOTE: default value
	_pio_info_g.osr_shift_right	= osr_shift_right;	// NOTE: default value

	if (isr_autopush_threshold < 0 || isr_autopush_threshold > 32) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal isr_autopush_threshold value.\n");
		exit(1);
	}
	if (osr_autopull_threshold < 0 || osr_autopull_threshold > 32) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal osr_autopull_threshold value.\n");
		exit(1);
	}
	_pio_info_g.isr_autopush			= isr_autopush;
	_pio_info_g.isr_autopush_threshold	= isr_autopush_threshold;	// NOTE: default value
	_pio_info_g.osr_autopull			= osr_autopull;
	_pio_info_g.osr_autopull_threshold	= osr_autopull_threshold;	// NOTE: default value

	_pio_info_g.isr_bitctr		= 0;		// empty
	_pio_info_g.osr_bitctr		= _pio_info_g.osr_autopull_threshold;	// (empty)


	{	// check # of sideset num
		if (sideset_num > 5 || (sideset_opt == true && sideset_num > 4)) {
			fprintf(stderr, "pio_code_start(): ERROR. Too many number of sideset signals.\n");
			exit(1);
		}

		if (sideset_opt == false) {
			delay_bitnum	= 5 - sideset_num;
		}
		else {
			delay_bitnum	= 4 - sideset_num;
		}

		_pio_info_g.sideset_maxval	= pio_maxval(sideset_num);

		if (delay_bitnum >= 1)
			_pio_info_g.delay_maxval	= pio_maxval(delay_bitnum);
		else
			_pio_info_g.delay_maxval	= 0;
	}

	_pio_info_g.jmp_pin		= jmp_pin;
	if (jmp_pin != PIO_UNUSE) {	// check jmp pin
		if (jmp_pin < 0 || jmp_pin > 29) {
			fprintf(stderr, "pio_code_start(): ERROR. Illegal jmp_pin assignment.\n");
			exit(1);
		}

		_pio_info_g.jmp_pin_setmask	= ((uint32_t)1 << jmp_pin) & 0x1FFFFFFF;	// GPIO28-0

		if ((_pio_info_g.jmp_pin_setmask & _pio_info_g.out_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Jmp_pin is assigned to an output port.\n");
			exit(1);
		}
		if ((_pio_info_g.jmp_pin_setmask & _pio_info_g.sideset_pin_setmask) != 0) {
			fprintf(stderr, "pio_code_start(): ERROR. Jmp_pin is assigned to a sideset port.\n");
			exit(1);
		}
	}

	_pio_info_g.mov_status_sel		= mov_status_sel;	// true:TX, false:RX
	if (mov_status_val < 1 || mov_status_val > 4) {
		fprintf(stderr, "pio_code_start(): ERROR. Illegal mov_status_val (1-4).\n");
		exit(1);
	}
	_pio_info_g.mov_status_val		= mov_status_val;

	_pio_info_g.wrap_target_line	= PIO_UNUSE;
	_pio_info_g.wrap_line			= PIO_UNUSE;

	_pio_info_g.fin					= (FILE *)NULL;
	_pio_info_g.fout				= (FILE *)NULL;
	_pio_info_g.fcode				= (FILE *)NULL;

	_pio_info_g.csvin_cache[0]		= '\0';
	_pio_info_g.csvin_cache_valid	= false;
	{
		_PIO_CSVIN	*p;
		p				= &(_pio_info_g.csvin_info);
		p->cycles		= PIO_UNUSE;
		p->gpio_i		= 0;
		p->txfifo_push	= false;
		p->txfifo_val	= 0;
		p->rxfifo_pop	= false;
	}
}


void pio_code_start_simple(
	char	*funcname, 
	int		sm_id,					// state machine ID (will be used for IRQ rel)
	int		in_pins, 
	int		in_num, 
	int		out_pins, 
	int		out_num, 
	int		sideset_pins, 
	int		sideset_num, 
	bool	sideset_opt
)
{
	pio_code_start(
		funcname, 
		sm_id,

		in_pins, 
		in_num, 
		out_pins, 
		out_num, 
		sideset_pins, 
		sideset_num, 
		sideset_opt, 

		false,			// bool	isr_shift_right, 		// SHIFTCTRL_IN_SHITDIR
		false,			// bool	isr_autopush,
		32,				// int	isr_autopush_threshold,	// SHIFTCTRL_PUSH_THRESH
		true,			// bool	osr_shift_right, 		// SHIFTCTRL_OUT_SHIFTDIR
		false,			// bool	osr_autopull,
		32,				// int	osr_autopull_threshold,	// SHIFTCTRL_PULL_THRESH
		PIO_UNUSE,		// int	jmp_pin,				// EXECCTRL_JMP_PIN
		true,			// bool	mov_status_sel,			// EXECCTRL_STATUS_SEL
		4				// int	mov_status_val			// EXECCTRL_STATUS_SEL
	);
}


static bool pio_get_asmline_pc(int *asmline, int pc)
{
	int	i;
	*asmline	= PIO_UNUSE;
	pc			&= 31;

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			return false;
		if (inst->addr == pc) {
			*asmline	= inst->code_line;	// IMPORTANT: return assember line
			return true;
		}
	}
	return false;
}


static bool pio_get_label_address(int *asmline, char *lbl)
{
	int	i;
	*asmline	= PIO_UNUSE;

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			return false;
		if (inst->inst_type != PIO_INST_LABEL)
			continue;
		if (!strcmp(lbl, inst->strbuf)) {
//			*asmline	= inst->addr;		// BUG
			*asmline	= inst->code_line;	// IMPORTANT: return assember line
			return true;
		}
	}
	return false;
}


static void pio_resolve_label_address(void)
{
	int		i, asmline;
//	char	tmpbuf[PIO_MAX_ASMLINE_LEN + 1];

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			return;
		if (inst->inst_type != PIO_INST_JMP)
			continue;
		if (pio_get_label_address(&asmline, inst->strbuf) == false) {
			fprintf(stderr, "pio_resolve_label_address(): ERROR. Undefined label \"%s\" in step %d (\"%s\").\n", inst->strbuf, inst->code_line, inst->asmbuf);
			exit(1);
		}
		else {
			inst->operand2	= asmline;		// IMPORTANT: assembler line
//fprintf(stderr, "resolve_label step %d jmp to step %d\n", inst->code_line, asmline);
// for debug
//			sprintf(tmpbuf, "\t; to addr 0x%02x", addr);
//			strcat(inst->asmbuf, tmpbuf);
		}
	}
}


static void pio_write_assembler_code(char *file_name_code)
{
	int		i;
	FILE	*fp;

	if ((_pio_info_g.fcode = fopen(file_name_code, "wt")) == (FILE *)NULL) {
		fprintf(stderr, "pio_write_assembler_code(): ERROR. Cannot create output ASM file \"%s\".\n", file_name_code);
		exit(1);
	}
	fp	= _pio_info_g.fcode;

	fprintf(fp, "; automatically generated by picopio_emu\n");
	fprintf(fp, "\n");

	// write header
	fprintf(fp, ".program %s\n", _pio_info_g.func_name);

	if (_pio_info_g.sideset_num > 0) {
		fprintf(fp, ".side_set %d", _pio_info_g.sideset_num);
		if (_pio_info_g.sideset_opt == true) {
			fprintf(fp, " opt");
		}
		fprintf(fp, "\n\n");
	}

	// write each instruction
	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*inst;
		inst	= &(_pio_info_g.asmline[i]);
		if (inst->used == false)
			break;

		// write code
#ifdef DISP_ASM_STDOUT
		fprintf(stdout, "%03d (pc=0x%02x):\t", inst->code_line, inst->addr);
#endif
		if (inst->inst_type != PIO_INST_COMMENT
					&& inst->inst_type != PIO_INST_LABEL
					&& inst->inst_type != PIO_INST_WRAP_TARGET
					&& inst->inst_type != PIO_INST_WRAP
					&& inst->inst_type != PIO_INST_ORIGIN) {
			fprintf(fp,     "\t");
#ifdef DISP_ASM_STDOUT
			fprintf(stdout, "\t");
#endif
		}
		fprintf(fp,     "%s\t; line %03d\n", inst->asmbuf, inst->code_line);
#ifdef DISP_ASM_STDOUT
		fprintf(stdout, "%s\n", inst->asmbuf);
#endif
	}

	// write C interface
	fprintf(fp, "\n");
	fprintf(fp, "%% c-sdk {\n");
	fprintf(fp, "// see also (api):   https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__pio.html\n");
	fprintf(fp, "// see also (pio.h): https://raspberrypi.github.io/pico-sdk-doxygen/rp2__common_2hardware__pio_2include_2hardware_2pio_8h_source.html\n");
	fprintf(fp, "// see also (sm):    https://raspberrypi.github.io/pico-sdk-doxygen/group__sm__config.html\n");
	fprintf(fp, "\n");

	fprintf(fp, "void %s_config(\n", _pio_info_g.func_name);
	fprintf(fp, "	PIO		pio,\n");
	fprintf(fp, "	uint	sm,\n");
	fprintf(fp, "	float	clkdiv\n");
	fprintf(fp, ")\n");
	fprintf(fp, "{\n");
	fprintf(fp, "	int		i;\n");
	fprintf(fp, "	uint	prog_addr;\n");
	fprintf(fp, "\n");

	fprintf(fp, "	if (clkdiv < 1.0) {\n");
	fprintf(fp, "		printf(\"asm_exec(): too small clkdiv\\n\");\n");
	fprintf(fp, "		return;\n");
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// load program to PIO\n");
	fprintf(fp, "	prog_addr			= pio_add_program(pio, &%s_program);\n", _pio_info_g.func_name);
	fprintf(fp, "	pio_sm_config	c	= %s_program_get_default_config(prog_addr);	// addr\n", _pio_info_g.func_name);
	fprintf(fp, "	sm_config_set_clkdiv(&c, clkdiv);	// pio_sm_config *c, float div\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// input\n");
	fprintf(fp, "	if (%d > 0) {\n", _pio_info_g.in_num);
	fprintf(fp, "		for (i = 0; i < %d; i++) {\n", _pio_info_g.in_num);
	fprintf(fp, "			pio_gpio_init(pio, %d + i);	// PIO pio, uint pin\n", _pio_info_g.in_pins);
//	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, %d, %d + i, 1, false);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sm_id, _pio_info_g.in_pins);
	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, sm, %d + i, 1, false);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.in_pins);
	fprintf(fp, "		}\n");
	fprintf(fp, "		sm_config_set_in_pins(&c, %d);	// pio_sm_config *c, uint in_base\n", _pio_info_g.in_pins);
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// sideset\n");
	fprintf(fp, "	if (%d > 0) {\n", _pio_info_g.sideset_num);
	fprintf(fp, "		for (i = 0; i < %d; i++) {\n", _pio_info_g.sideset_num);
	fprintf(fp, "			pio_gpio_init(pio, %d + i);	// PIO pio, uint pin\n", _pio_info_g.sideset_pins);
//	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, %d, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sm_id, _pio_info_g.sideset_pins);
	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, sm, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sideset_pins);
	fprintf(fp, "		}\n");
	fprintf(fp, "		sm_config_set_sideset_pins(&c, %d);	// pio_sm_config *c, uint sideset_base\n", _pio_info_g.sideset_pins);
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// output\n");
	fprintf(fp, "	if (%d > 0) {\n", _pio_info_g.out_num);
	fprintf(fp, "		for (i = 0; i < %d; i++) {\n", _pio_info_g.out_num);
	fprintf(fp, "			pio_gpio_init(pio, %d + i);	// PIO pio, uint pin\n", _pio_info_g.out_pins);
//	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, %d, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.sm_id, _pio_info_g.out_pins);
	fprintf(fp, "			pio_sm_set_consecutive_pindirs(pio, sm, %d + i, 1, true);	// PIO pio, uint sm, uint pin_base, uint pin_count, bool is_out\n", _pio_info_g.out_pins);
	fprintf(fp, "		}\n");
	fprintf(fp, "		if (%d <= 5)", _pio_info_g.out_num);
	fprintf(fp, "			sm_config_set_set_pins(&c, %d, %d);	// pio_sm_config *c, uint set_base, uint set_count\n", _pio_info_g.out_pins, _pio_info_g.out_num);
	fprintf(fp, "		else\n");
	fprintf(fp, "			sm_config_set_set_pins(&c, %d, 5);	// pio_sm_config *c, uint set_base, uint set_count\n", _pio_info_g.out_pins);
	fprintf(fp, "		sm_config_set_out_pins(&c, %d, %d);	// pio_sm_config *c, uint out_base, uint out_count\n", _pio_info_g.out_pins, _pio_info_g.out_num);
	fprintf(fp, "	}\n");
	fprintf(fp, "\n");

	fprintf(fp, "	// fifo, isr and osr\n");
//	fprintf(fp, "	sm_config_set_in_shift(&c, false, false, 32);		// shift right, auto-push, threshold\n");
	fprintf(fp, "	sm_config_set_in_shift(&c, ");
	if (_pio_info_g.isr_shift_right == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	if (_pio_info_g.isr_autopush == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	fprintf(fp, "%d);		// pio_sm_config *c, bool shift_right, bool autopush, uint push_threshold\n", _pio_info_g.isr_autopush_threshold);

	fprintf(fp, "	sm_config_set_out_shift(&c, ");
	if (_pio_info_g.osr_shift_right == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	if (_pio_info_g.osr_autopull == false)
		fprintf(fp, "false, ");
	else
		fprintf(fp, "true, ");
	fprintf(fp, "%d);		// pio_sm_config *c, bool shift_right, bool autopull, uint pull_threshold\n", _pio_info_g.osr_autopull_threshold);
	fprintf(fp, "\n");

	if (_pio_info_g.jmp_pin != PIO_UNUSE) {
		fprintf(fp, "	// \"jmp pin\" instruction\n");
		fprintf(fp, "	sm_config_set_jmp_pin(&c, %d);	// pio_sm_config *c, uint pin\n", _pio_info_g.jmp_pin);
		fprintf(fp, "\n");
	}

	fprintf(fp, "	// \"move status\" instruction\n");
 	fprintf(fp, "	sm_config_set_mov_status(&c, ");
	if (_pio_info_g.mov_status_sel == true)
		fprintf(fp, "STATUS_TX_LESSTHAN, ");
	else
		fprintf(fp, "STATUS_RX_LESSTHAN, ");
	fprintf(fp, "%d);	// pio_sm_config *c, enum pio_mov_status_type status_sel, uint status_n\n", _pio_info_g.mov_status_val);
	fprintf(fp, "\n");

//	fprintf(fp, "	pio_sm_clear_fifos(pio, %d);	// PIO pio, uint sm\n", _pio_info_g.sm_id);
	fprintf(fp, "	pio_sm_clear_fifos(pio, sm);	// PIO pio, uint sm\n");
//	fprintf(fp, "	pio_sm_init(pio, %d, prog_addr, &c);	// PIO pio, uint sm, uint initial_pc, const pio_sm_config *config\n", _pio_info_g.sm_id);
	fprintf(fp, "	pio_sm_init(pio, sm, prog_addr, &c);	// PIO pio, uint sm, uint initial_pc, const pio_sm_config *config\n");
//	fprintf(fp, "	pio_sm_set_enabled(pio, sm, true);	// PIO pio, uint sm, bool enabled\n");
	fprintf(fp, "}\n");

	fprintf(fp, "%%}\n");

	fclose(_pio_info_g.fcode);
}


void pio_code_end(bool write_code, char *file_name_code)
{
	if (_pio_emu_state_g != PIO_SIMSTATE_CODE_END) {
		fprintf(stderr, "pio_code_end(): ERROR. Illegal code-end position.\n");
		exit(1);
	}
	_pio_emu_state_g	= PIO_SIMSTATE_RUN_START;

	pio_resolve_label_address();
	if (write_code == true) {
		pio_write_assembler_code(file_name_code);		// create output asm
	}
}


static int pio_search_wrap_target(void)
{
	int	i;
	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*ap;
		ap	= &(_pio_info_g.asmline[i]);
		if (ap->used == false)
			break;
		if (ap->inst_type == PIO_INST_WRAP_TARGET)
			return i;
	}
	return 0;	// not found: return to top of the list
}


static void pio_read_csv_input_header(void)
{
	FILE		*fp;
	if ((fp = _pio_info_g.fin) == (FILE *)NULL)
		return;
	if (feof(fp))
		return;

	// cut 1st line of the csv
	fgets(_pio_info_g.csvin_cache, PIO_MAX_CSVLINE_LEN - 1, fp);
	_pio_info_g.csvin_cache_valid = false;
}


static void pio_shift_txfifo(void)
{
	int	i;
	for (i = 0; i < 3; i++) {
		_pio_info_g.txfifo[i]	= _pio_info_g.txfifo[i + 1];
	}
	_pio_info_g.txfifo[3]	= 0;
}


static void pio_shift_rxfifo(void)
{
	int	i;
	for (i = 0; i < 3; i++) {
		_pio_info_g.rxfifo[i]	= _pio_info_g.rxfifo[i + 1];
	}
	_pio_info_g.rxfifo[3]	= 0;
}


static bool pio_push_txfifo(uint32_t val)
{
	switch (_pio_info_g.txfifo_num) {
	case 0:
		_pio_info_g.txfifo[0]	= val;
		_pio_info_g.txfifo_num	= 1;
		return true;
	case 1:
		_pio_info_g.txfifo[1]	= val;
		_pio_info_g.txfifo_num	= 2;
		return true;
	case 2:
		_pio_info_g.txfifo[2]	= val;
		_pio_info_g.txfifo_num	= 3;
		return true;
	case 3:
		_pio_info_g.txfifo[3]	= val;
		_pio_info_g.txfifo_num	= 4;
		return true;
	default:
		break;
	}
	return false;
}


static bool pio_pop_txfifo(uint32_t *val)
{
	switch (_pio_info_g.txfifo_num) {
	case 4:
	case 3:
	case 2:
	case 1:
		*val	= _pio_info_g.txfifo[0];
		(_pio_info_g.txfifo_num)--;
		pio_shift_txfifo();
		return true;
	default:
		break;
	}
	*val	= 0;
	return false;
}


static bool pio_push_rxfifo(uint32_t val)
{
	switch (_pio_info_g.rxfifo_num) {
	case 0:
		_pio_info_g.rxfifo[0]	= val;
		_pio_info_g.rxfifo_num	= 1;
		return true;
	case 1:
		_pio_info_g.rxfifo[1]	= val;
		_pio_info_g.rxfifo_num	= 2;
		return true;
	case 2:
		_pio_info_g.rxfifo[2]	= val;
		_pio_info_g.rxfifo_num	= 3;
		return true;
	case 3:
		_pio_info_g.rxfifo[3]	= val;
		_pio_info_g.rxfifo_num	= 4;
		return true;
	default:
		break;
	}
	return false;
}


static bool pio_pop_rxfifo(uint32_t *val)
{
	switch (_pio_info_g.rxfifo_num) {
	case 4:
	case 3:
	case 2:
	case 1:
		*val	= _pio_info_g.rxfifo[0];
		(_pio_info_g.rxfifo_num)--;
		pio_shift_rxfifo();
		return true;
	default:
		break;
	}
	*val	= 0;
	return false;
}


static void pio_copy_csvin_to_input(void)
{
	uint32_t	tmp;

	// GPIO
	_pio_info_g.gpio_i	= (_pio_info_g.csvin_info.gpio_i) & _pio_info_g.in_pin_setmask;		// IMPORTANT: apply mask
	_pio_info_g.gpio_o	= (_pio_info_g.gpio_o & _pio_info_g.in_pin_clrmask)
							| _pio_info_g.gpio_i;											// IMPORTANT: copy input value to output

	// IRQ ACK
	_pio_info_g.irq_i	= _pio_info_g.csvin_info.irq_i;
	_pio_info_g.irq_o	|= _pio_info_g.csvin_info.irq_i;

	// TX fifo
	if (_pio_info_g.csvin_info.txfifo_push == true) {
		if (pio_push_txfifo(_pio_info_g.csvin_info.txfifo_val) == false) {
			fprintf(stderr, "pio_copy_csvinfo_to_input(): WARNING. Cannot push data to tx-fifo (in cycle %d).\n", _pio_info_g.cycles);
		}
	}

	// RX fifo
	if (_pio_info_g.csvin_info.rxfifo_pop == true) {
		if (pio_pop_rxfifo(&tmp) == false) {
			fprintf(stderr, "pio_copy_csvinfo_to_input(): WARNING. Cannot pop data from rx-fifo (in cycle %d).\n", _pio_info_g.cycles);
		}
	}
}


static void pio_read_csv_input(void)
{
	FILE		*fp;
	if ((fp = _pio_info_g.fin) == (FILE *)NULL)
		return;
	if (feof(fp))
		return;

	// - read csv until exec cycle >= csv cycle
	// - update input value if exec cycle == csv cycle
	// - csv format: "cycle, gpio_i, irq_i, tx_push(0/1), tx_val, rx_pop(0/1)\n"
	while (1) {
		if (_pio_info_g.csvin_cache_valid == false) {
			int	b0, b1, i0;
#ifdef	PIO_IN_GPIO_BIT_BY_BIT
			int	gp[29];	// 29 ... GPIO 0-28
#endif

			// read line
			if (fgets(_pio_info_g.csvin_cache, PIO_MAX_CSVLINE_LEN - 1, fp) == NULL)
				return;

			// scan line
#ifdef	PIO_IN_GPIO_BIT_BY_BIT
			sscanf(_pio_info_g.csvin_cache, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 0x%x, %d, 0x%x, %d\n",
						&(_pio_info_g.csvin_info.cycles),
						&(gp[0]), &(gp[1]), &(gp[2]), &(gp[3]), &(gp[4]), &(gp[5]), &(gp[6]), &(gp[7]), &(gp[8]), &(gp[9]),
						&(gp[10]), &(gp[11]), &(gp[12]), &(gp[13]), &(gp[14]), &(gp[15]), &(gp[16]), &(gp[17]), &(gp[18]), &(gp[19]),
						&(gp[20]), &(gp[21]), &(gp[22]), &(gp[23]), &(gp[24]), &(gp[25]), &(gp[26]), &(gp[27]), &(gp[28]),
						&i0,
						&b0,
						&(_pio_info_g.csvin_info.txfifo_val),
						&b1
					);
			{
				int			i;
				uint32_t	v;
				v	= 0;
				for (i = 0; i < 29; i++) {	// 29 ... GPIO 0-28
					v	<<= 1;
					if (gp[28 - i] != 0) {
						v	|= 1;
					}
				}
				_pio_info_g.csvin_info.txfifo_val	= v;
			}
#else
			sscanf(_pio_info_g.csvin_cache, "%d, 0x%x, 0x%x, %d, 0x%x, %d\n",
						&(_pio_info_g.csvin_info.cycles),
						&(_pio_info_g.csvin_info.gpio_i),
						&i0,
						&b0,
						&(_pio_info_g.csvin_info.txfifo_val),
						&b1
					);
#endif
			_pio_info_g.csvin_info.irq_i	= (uint8_t)i0;

			if (b0 == 0)
				_pio_info_g.csvin_info.txfifo_push	= false;
			else
				_pio_info_g.csvin_info.txfifo_push	= true;
			if (b1 == 0)
				_pio_info_g.csvin_info.rxfifo_pop	= false;
			else
				_pio_info_g.csvin_info.rxfifo_pop	= true;
//fprintf(stderr, "%s", _pio_info_g.csvin_cache);
//fprintf(stderr, "cycle %d\n", _pio_info_g.csvin_info.cycles);
//fprintf(stderr, "gpio %08x\n", _pio_info_g.csvin_info.gpio_i);
//fprintf(stderr, "push %d\n", b0);
//fprintf(stderr, "pop %d\n", b1);
		}

		// update info
		if (_pio_info_g.cycles > _pio_info_g.csvin_info.cycles) {	// (past)
			pio_copy_csvin_to_input();
			_pio_info_g.csvin_cache_valid = false;
#ifdef DISP_TRACE_STDOUT
			fprintf(stdout, "\tREAD CSV (cycle %d)\n", _pio_info_g.csvin_info.cycles);
#endif
		}
		else if (_pio_info_g.cycles == _pio_info_g.csvin_info.cycles) {	// (current)
			pio_copy_csvin_to_input();
			_pio_info_g.csvin_cache_valid = false;
#ifdef DISP_TRACE_STDOUT
			fprintf(stdout, "\tREAD CSV (cycle %d)\n", _pio_info_g.csvin_info.cycles);
#endif
			return;
		}
		else {	// (future)
			// (nothing to do)
			_pio_info_g.csvin_cache_valid = true;
			return;
		}
	}	// while
}


static bool pio_is_assigned_pin(int num)
{
	uint32_t	pin;
	pin	= (uint32_t)1 << num;

	if ((_pio_info_g.in_pin_setmask & pin) != 0)
		return true;
	if ((_pio_info_g.out_pin_setmask & pin) != 0)
		return true;
	if ((_pio_info_g.sideset_pin_setmask & pin) != 0)
		return true;

	return false;
}


static void pio_write_csv_output_header(void)
{
	FILE		*fp;
	int			i;

	if ((fp = _pio_info_g.fout) == (FILE *)NULL)
		return;

	fprintf(fp, "cycle, ");
	fprintf(fp, "line, ");
	fprintf(fp, "pc, ");
	fprintf(fp, "inst, ");

#ifdef	PIO_OUT_GPIO_BIT_BY_BIT
	for (i = 0; i < 29; i++) {	// 29 ... GPIO 0-28
		if (pio_is_assigned_pin(i) == true) {
			fprintf(fp, "gpio_%d, ", i);
		}
	}
#else
	fprintf(fp, "gpio, ");
#endif

	fprintf(fp, "irq, ");
	fprintf(fp, "x, ");
	fprintf(fp, "y, ");
	fprintf(fp, "isr_bitctr, ");
	fprintf(fp, "isr, ");
	fprintf(fp, "osr_bitctr, ");
	fprintf(fp, "osr, ");
	fprintf(fp, "txfifo_num, ");
	fprintf(fp, "txfifo[0], ");
	fprintf(fp, "txfifo[1], ");
	fprintf(fp, "txfifo[2], ");
	fprintf(fp, "txfifo[3], ");
	fprintf(fp, "rxfifo_num, ");
	fprintf(fp, "rxfifo[0], ");
	fprintf(fp, "rxfifo[1], ");
	fprintf(fp, "rxfifo[2], ");
	fprintf(fp, "rxfifo[3]");
	fprintf(fp, "\n");
}

static void pio_write_csv_output_inst(void)
{
	_PIO_INST	*ap;
	FILE		*fp;
	char		tmpbuf[PIO_MAX_ASMLINE_NUM];

	if ((fp = _pio_info_g.fout) == (FILE *)NULL)
		return;

	ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);

	// - write csv output every cycle
	fprintf(fp, "%d, ", _pio_info_g.cycles);
	fprintf(fp, "%d, ", ap->code_line);
	fprintf(fp, "0x%02x, ", ap->addr);
	if (_pio_info_g.delay_timer > 0)
		fprintf(fp, "\"delay\", ");
	else {
		char	*p;
		strcpy(tmpbuf, ap->asmbuf);
		for (p = tmpbuf; *p != '\0'; p++) {
			if (*p == '\t')
				*p	= ' ';
			else if (*p == ',')
				*p	= ' ';
		}
		fprintf(fp, "\"%s\", ",tmpbuf);
	}
}


static void pio_write_csv_output_regs(void)
{
	_PIO_INST	*ap;
	FILE		*fp;
	uint32_t	val;
	int			i;

	if ((fp = _pio_info_g.fout) == (FILE *)NULL)
		return;

	ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);

	// - write csv output every cycle
#ifdef	PIO_OUT_GPIO_BIT_BY_BIT
	val	= _pio_info_g.gpio_o;
	for (i = 0; i < 29; i++) {	// 29 ... GPIO 0-28
		if (pio_is_assigned_pin(i) == true) {
			if ((val & 1) != 0)
				fprintf(fp, "1, ");
			else
				fprintf(fp, "0, ");
		}
		val	>>=	1;
	}
#else
	fprintf(fp, "0x%08x, ", _pio_info_g.gpio_o);
#endif

	fprintf(fp, "0x%02x, ", _pio_info_g.irq_o);
	fprintf(fp, "0x%08x, ", _pio_info_g.x);
	fprintf(fp, "0x%08x, ", _pio_info_g.y);
	fprintf(fp, "%d, ",		_pio_info_g.isr_bitctr);
	fprintf(fp, "0x%08x, ", _pio_info_g.isr);
	fprintf(fp, "%d, ",		_pio_info_g.osr_bitctr);
	fprintf(fp, "0x%08x, ", _pio_info_g.osr);

	fprintf(fp, "%d, ", _pio_info_g.txfifo_num);
	for (i = 0; i < 4; i++) {
		fprintf(fp, "0x%08x, ", _pio_info_g.txfifo[i]);
	}
	fprintf(fp, "%d, ", _pio_info_g.rxfifo_num);
//	for (i = 0; i < 4; i++) {
	for (i = 0; i < 3; i++) {
		fprintf(fp, "0x%08x, ", _pio_info_g.rxfifo[i]);
	}
	fprintf(fp, "0x%08x", _pio_info_g.rxfifo[3]);
	fprintf(fp, "\n");
}


static bool pio_check_existence_of_code(void)
{
	int		inst, i;
	bool	ret	= false;

	for (i = 0; i < PIO_MAX_ASMLINE_NUM; i++) {
		_PIO_INST	*ap;
		ap		= &(_pio_info_g.asmline[i]);
		inst	= ap->inst_type;
		if (ap->used == false)
			break;
		if (inst == PIO_INST_WRAP_TARGET) {
			ret	= false;	// IMPORTANT: reset flag
			continue;
		}
		if (inst == PIO_INST_COMMENT || inst == PIO_INST_LABEL || inst == PIO_INST_WRAP_TARGET || inst == PIO_INST_WRAP || inst == PIO_INST_ORIGIN)
			continue;

//		return true;	// IMPORTANT: do not return
		ret	= true;
	}
	return ret;
}


static uint32_t pio_input_inpin_value(void)
{
	uint32_t	ret;
	ret	= (_pio_info_g.gpio_i & _pio_info_g.in_pin_setmask) >> (_pio_info_g.in_pins);
	return ret;
}


static void pio_output_outpin_value(uint32_t val)
{
	uint32_t	real_val;
	real_val	= (val << (_pio_info_g.out_pins)) & _pio_info_g.out_pin_setmask;
	_pio_info_g.gpio_o	= (_pio_info_g.gpio_o & _pio_info_g.out_pin_clrmask)
									| real_val;
}


static void pio_output_sideset_value(int sideset)
{
	if (_pio_info_g.sideset_opt == true || sideset != PIO_UNUSE) {
		if (sideset != PIO_UNUSE) {
			_pio_info_g.sideset_val	= (sideset << (_pio_info_g.sideset_pins)) & _pio_info_g.sideset_pin_setmask;
		}
		_pio_info_g.gpio_o	= (_pio_info_g.gpio_o & _pio_info_g.sideset_pin_clrmask)
									| _pio_info_g.sideset_val;
	}
}


static void pio_exec_instruction(void)
{
	_PIO_INST	*ap;
	int 		inst, op1, op2, op3, op4, op5;
	int 		sideset, delay;
	char 		*str;
	int			linenum;
	uint8_t		addr;

	bool		autopull_failure, autopull_done;

	/////////////////////////////////////////////////////////
	// return immediately if executing delay cycles
	/////////////////////////////////////////////////////////
	if (_pio_info_g.delay_timer > 0) {
		pio_write_csv_output_inst();
		pio_write_csv_output_regs();
#ifdef DISP_TRACE_STDOUT
		fprintf(stdout, "cycle %d\t\t\tDELAY\n", _pio_info_g.cycles);
#endif

		(_pio_info_g.delay_timer)--;		// decrement delay timer
		(_pio_info_g.cycles)++;				// increment cycle counter
		return;
	}

	/////////////////////////////////////////////////////////
	// cut pseudo instructions
	/////////////////////////////////////////////////////////
	while (1) {
		ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);
		inst	= ap->inst_type;

		if (ap->used == false) {			// reached to the end of code list
			_pio_info_g.asmline_ptr	= 0;
			continue;
		}
		else if (inst == PIO_INST_COMMENT || inst == PIO_INST_LABEL || inst == PIO_INST_WRAP_TARGET || inst == PIO_INST_ORIGIN) {
			// skip this code
			(_pio_info_g.asmline_ptr)++;
			if (_pio_info_g.asmline_ptr >= PIO_MAX_ASMLINE_NUM) {
				_pio_info_g.asmline_ptr	= 0;
			}
			continue;
		}
		else if (inst == PIO_INST_WRAP) {
			// jump to wrap target
			_pio_info_g.asmline_ptr	= pio_search_wrap_target();
		}
		else
			break;
	};

	/////////////////////////////////////////////////////////
	// update input
	/////////////////////////////////////////////////////////
	pio_read_csv_input();

	/////////////////////////////////////////////////////////
	// autopull operation (if specified)
	/////////////////////////////////////////////////////////
	autopull_failure	= false;
	autopull_done		= false;

	if (_pio_info_g.osr_autopull == true && _pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold) {	// reached to autopull threshold
		uint32_t	pop_val;
		if (pio_pop_txfifo(&pop_val) == true) {
			_pio_info_g.osr			= pop_val;
			_pio_info_g.osr_bitctr	= 0;			// (full)
#ifdef DISP_TRACE_STDOUT
			fprintf(stdout, "\tAUTOPULL\n");
#endif
			autopull_done		= true;
		}
		else {
			autopull_failure	= true;
		}
	}

	/////////////////////////////////////////////////////////
	// exec instruction
	/////////////////////////////////////////////////////////
	op1		= ap->operand1;
	op2		= ap->operand2;
	op3		= ap->operand3;
	op4		= ap->operand4;
	op5		= ap->operand5;
	sideset	= ap->sideset;
	delay	= ap->delay;
	str		= ap->strbuf;
	linenum	= ap->code_line;
	addr	= ap->addr;

	pio_write_csv_output_inst();		// write instruction BEFORE executing instruction
#ifdef DISP_TRACE_STDOUT
	fprintf(stdout, "cycle %d, line %d, pc=%d\t%s\n", _pio_info_g.cycles, ap->code_line, ap->addr, ap->asmbuf);
#endif

	switch (inst) {
	/////////////////////////////////
	// JMP
	/////////////////////////////////
	case PIO_INST_JMP: {
		bool		jmpcond;
		uint32_t	pinval;

		// condition
		switch (op1) {
		case PIO_ALWAYS:
			jmpcond	= true;
			break;

		case PIO_X_EQ_0:
			jmpcond	= (_pio_info_g.x == 0)	? true : false;
			break;

		case PIO_X_NEQ_0_DEC:
			jmpcond	= (_pio_info_g.x != 0)	? true : false;
			(_pio_info_g.x)--;		// post decrement
			break;

		case PIO_Y_EQ_0:
			jmpcond	= (_pio_info_g.y == 0)	? true : false;
			break;

		case PIO_Y_NEQ_0_DEC:
			jmpcond	= (_pio_info_g.y != 0)	? true : false;
			(_pio_info_g.y)--;		// post decrement
			break;

		case PIO_X_NEQ_Y:
			jmpcond	= (_pio_info_g.x != _pio_info_g.y)	? true : false;
			break;

		case PIO_PIN:
			if (_pio_info_g.jmp_pin == PIO_UNUSE) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. No pin assignment is given to JMP_PIN (JMP in step %d).\n", linenum);
				exit(1);
			}
			else {
				pinval	= _pio_info_g.jmp_pin_setmask & _pio_info_g.gpio_i;
				jmpcond	= (pinval != 0)	? true : false;		// jmp if gpio(EXECCTRL_JMP_PIN) == 1
			} 
			break;

		case PIO_OSRE_NOTEMPTY:
//			jmpcond	= (_pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold)	? true : false;	// BUG
			jmpcond	= (_pio_info_g.osr_bitctr < _pio_info_g.osr_autopull_threshold)	? true : false;
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal condition (JMP in step %d).\n", linenum);
			exit(1);
		} // op1

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (jmpcond == false)
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
		else {
			_pio_info_g.asmline_ptr	= op2;	// jump to the specified line (INST_LABEL)
		}

		if (delay > 0) {					// set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	/////////////////////////////////
	// WAIT
	/////////////////////////////////
	case PIO_INST_WAIT: {
		bool		stall;

		int			pin_in;
		uint32_t	pin_mask;
		int			pin_value;

		bool		rel;
		int			irq_num;
		uint8_t		irq_setmask, irq_clrmask;

		// source
		switch (op2) {
		case PIO_GPIO:
			if (op3 < 0 || op3 > 29) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal GPIO assignment (WAIT in step %d).\n", linenum);
				exit(1);
			}
			pin_mask	= ((uint32_t)1 << op3) & 0x1FFFFFFF;	// GPIO28-0
			if ((pin_mask & _pio_info_g.out_pin_setmask) != 0) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Reffering to an output port (WAIT in step %d).\n", linenum);
				exit(1);
			}
			if ((pin_mask & _pio_info_g.sideset_pin_setmask) != 0) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Reffering to an sideset port (WAIT in step %d).\n", linenum);
				exit(1);
			}

			pin_value	= ((_pio_info_g.gpio_i & pin_mask) != 0)	? 1 : 0;
			stall		= (op1 == pin_value)						? false : true;		// polarity
			break;

		case PIO_PIN:
			if (_pio_info_g.in_num <= 0) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. No input pin is assigned (WAIT in step %d).\n", linenum);
				exit(1);
			}
			if (op3 < 0 || op3 > _pio_info_g.in_num - 1) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal index value (WAIT in step %d).\n", linenum);
				exit(1);
			}
			pin_in		= (_pio_info_g.in_pins + op3) % 32;
			pin_mask	= ((uint32_t)1 << pin_in) & 0x1FFFFFFF;		// GPIO28-0
			pin_value	= ((_pio_info_g.gpio_i & pin_mask) != 0)	? 1 : 0;
			stall		= (op1 == pin_value)						? false : true;		// polarity
			break;

		case PIO_IRQ:
			rel		= (op4 == 1)	? true : false;

			// calc actual IRQ number
			irq_num	= op3 & 0x07;						// bit2-0
// NEEDS SPEC CHECK HERE
			if (rel == true || (op3 & 0x10) != 0) {		// rel == 1 or MSB of index == 1
				irq_num	= ((irq_num + _pio_info_g.sm_id) & 0x03)		// module 4 addition to bit 1-0
							| (op3 & 0x0C);								// no effect to bit 3-2
			}
			if (0 > irq_num || irq_num > 7) {
				fprintf(stderr, "pio_exec_instruction(): Internal ERROR. Illegal irq_num (WAIT in step %d).\n", linenum);
				exit(1);
			}

			irq_setmask	= (uint8_t)1 << irq_num;
			irq_clrmask	= irq_setmask ^ 0xFF;

			// status check
			if (op1 == 1 && (_pio_info_g.irq_i & irq_setmask) != 0) {		// wait for 1
				stall	= false;
// NEEDS SPEC CHECK HERE
				_pio_info_g.irq_o	&= irq_clrmask;		// clear INT
				_pio_info_g.irq_i	&= irq_clrmask;		// IMPORTANT: reflect to irq_in_buf
			}
			else if (op1 == 0 && (_pio_info_g.irq_i & irq_setmask) == 0) {	// wait for 0
				stall	= false;
			}
			else {
				stall	= true;
			}
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal source (WAIT in step %d).\n", linenum);
			exit(1);
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

//		if (stall == false) {
		if (stall == false && _pio_info_g.irq_stalling == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { 				// set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}
		// else stall 	IMPORTANT NOTE: delay is NOT executed while stalling

		} break;

	/////////////////////////////////
	// IN
	/////////////////////////////////
	case PIO_INST_IN: {
		uint32_t	src_val, newisr_val;
		int			shift_amount;
		bool		stall;

		if (op2 <= 0 || op2 > 32) {
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal bit count (IN in step %d).\n", linenum);
			exit(1);
		}
		shift_amount	= op2;

		// source
		switch (op1) {
		case PIO_PINS:
			src_val	= pio_input_inpin_value();
			break;

		case PIO_X:
			src_val	= _pio_info_g.x;
			break;

		case PIO_Y:
			src_val	= _pio_info_g.y;
			break;

		case PIO_NULL:
			src_val	= 0;
			break;

		case PIO_ISR:
			src_val	= _pio_info_g.isr;
			break;

		case PIO_OSR:
			src_val	= _pio_info_g.osr;
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal source (IN in step %d).\n", linenum);
			exit(1);
		}

		// dest
		src_val	&= pio_maxval(shift_amount);	// AND bitmask (use LSB side)
		if (_pio_info_g.isr_shift_right == true) {
			// right shift
			src_val	<<=	32 - shift_amount;
//			_pio_info_g.isr	= (_pio_info_g.isr >> shift_amount) | src_val;		// BUG
			newisr_val	= (_pio_info_g.isr >> shift_amount) | src_val;			// IMPORTANT: not substitute here, for autopush stall
		}
		else {
			// left shift
//			_pio_info_g.isr	= (_pio_info_g.isr << shift_amount) | src_val;		// BUG
			newisr_val	= (_pio_info_g.isr << shift_amount) | src_val;			// IMPORTANT: not substitute here, for autopush stall
		}

		// autopush and substitute
		stall	= false;

		if (_pio_info_g.isr_autopush == true && _pio_info_g.isr_bitctr + shift_amount >= _pio_info_g.isr_autopush_threshold) {
//			if (pio_push_rxfifo(_pio_info_g.isr) == true) {		// push operation	BUG
			if (pio_push_rxfifo(newisr_val) == true) {	// push operation
				_pio_info_g.isr			= 0;			// clear ISR
				_pio_info_g.isr_bitctr	= 0;			// (empty)
			}
			else {	// push failure
				stall	= true;							// wait until rxfifo has a empty space
			}
		}
		else {	// no autopush (normal operation)
			_pio_info_g.isr			= newisr_val;		// update ISR
			_pio_info_g.isr_bitctr	+= shift_amount;	// update ctr
			if (_pio_info_g.isr_bitctr > _pio_info_g.isr_autopush_threshold) {
				_pio_info_g.isr_bitctr	= _pio_info_g.isr_autopush_threshold;
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (stall == false) {	// go to next instruction if not stall
			(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// OUT
	/////////////////////////////////
	case PIO_INST_OUT: {
		uint32_t	dest_val;
		int			shift_amount;

		if (op2 <= 0 || op2 > 32) {
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal bit count (OUT in step %d).\n", linenum);
			exit(1);
		}
		shift_amount	= op2;

		// read osr
		if (_pio_info_g.osr_shift_right == true) {
			// get lsb
			dest_val		= _pio_info_g.osr & pio_maxval(shift_amount);
//			_pio_info_g.osr	>>= shift_amount;		// BUG: do not update here, for autopull stall
		}
		else {
			// get msb
			dest_val		= (_pio_info_g.osr >> (32 - shift_amount)) & pio_maxval(shift_amount);
//			_pio_info_g.osr	<<= shift_amount;		// BUG: do not update here, for autopull stall
		}

		// destination
		switch (op1) {
		case PIO_PINS:
			pio_output_outpin_value(dest_val);
			break;

		case PIO_X:
			_pio_info_g.x	= dest_val;
			break;

		case PIO_Y:
			_pio_info_g.y	= dest_val;
			break;

		case PIO_NULL:
			// do nothing, discard data
			break;

		case PIO_PINDIRS:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
// (Unsupported independent pin assignment between SET and OUT)
fprintf(stderr, "pio_exec_instruction(): WARNING. Unsupported destination PINDIRS, ignored (OUT in step %d).\n", linenum);
			break;

		case PIO_PC:
			break;

		case PIO_ISR:
			_pio_info_g.isr	= dest_val;
			break;

		case PIO_EXEC:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
fprintf(stderr, "pio_exec_instruction(): ERROR. Unsupported destination EXEC (OUT in step %d).\n", linenum);
exit(1);
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (OUT in step %d).\n", linenum);
			exit(1);
		}

		if (autopull_failure == false) {	// (tested at the top of exec cycle)
			// update osr
			if (_pio_info_g.osr_shift_right == true) {
				_pio_info_g.osr	>>= shift_amount;
			}
			else {
				_pio_info_g.osr	<<= shift_amount;
			}

			// update bitctr
			_pio_info_g.osr_bitctr	+= shift_amount;
			if (_pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold) {
				_pio_info_g.osr_bitctr	= _pio_info_g.osr_autopull_threshold;	// (empty)
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (autopull_failure == false) {	// (tested at the top of exec cycle)
			if (op1 != PIO_PC) {
				(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
			}
			else {	// OUT PC (unconditional jmp)
				int	asmline;
				if (pio_get_asmline_pc(&asmline, dest_val) == false) {
					fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (OUT in step %d).\n", linenum);
					exit(1);
				}
				_pio_info_g.asmline_ptr	= asmline;
			}

			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}
		// (else stall until autopull success)

		} break;

	/////////////////////////////////
	// PUSH
	/////////////////////////////////
	case PIO_INST_PUSH: {
		bool	push_done, iffull, block;
		bool	stall;
		iffull	= (op1 == 1)	? true : false;
		block	= (op2 == 1)	? true : false;

		stall	= false;

		if (iffull == false || _pio_info_g.isr_bitctr >= _pio_info_g.isr_autopush_threshold) {
			push_done		= pio_push_rxfifo(_pio_info_g.isr);		// push operation

			if (push_done == true) {
				_pio_info_g.isr			= 0;		// IMPORTANT: clear ISR
// SPECIFICATION UNCONFIRMED: clearing bitnum
				_pio_info_g.isr_bitctr	= 0;		// (empty)
			}
			else {	// push faliure
				if (block == true) {	// blocking
					stall	= true;
				}
				else {					// nonblocking
					_pio_info_g.isr			= 0;	// IMPORTANT: clear ISR
// SPECIFICATION UNCONFIRMED: clearing bitnum
					_pio_info_g.isr_bitctr	= 0;	// (empty)
				}
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (stall == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// PULL
	/////////////////////////////////
	case PIO_INST_PULL: {
		bool	pop_done, ifempty, block;
		bool	stall;
		uint32_t	pop_val;
		ifempty		= (op1 == 1)	? true : false;
		block		= (op2 == 1)	? true : false;

		stall	= false;

		if (autopull_done == false) {
			if (ifempty == false || _pio_info_g.osr_bitctr >= _pio_info_g.osr_autopull_threshold) {
				pop_done	= pio_pop_txfifo(&pop_val);		// pop operation

				if (pop_done == true) {
					_pio_info_g.osr			= pop_val;
// SPECIFICATION UNCONFIRMED: clearing bitnum
					_pio_info_g.osr_bitctr	= 0;			// (full)
				}
				else {	// pop failure
					if (block == true) {	// blocking
						stall	= true;
					}
					else {					// nonblocking
						_pio_info_g.osr			= _pio_info_g.x;	// IMPORTANT: mov x, osr
// SPECIFICATION UNCONFIRMED: clearing bitnum
						_pio_info_g.osr_bitctr	= 0;				// IMPORTANT (full)
					}
				}
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (stall == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// MOV
	/////////////////////////////////
	case PIO_INST_MOV: {
		uint32_t	src_val;

		// source
		switch (op3) {
		case PIO_PINS:
			src_val	= pio_input_inpin_value();
			break;

		case PIO_X:
			src_val	= _pio_info_g.x;
			break;

		case PIO_Y:
			src_val	= _pio_info_g.y;
			break;

		case PIO_NULL:
			src_val	= 0;
			break;

		case PIO_STATUS:
			// see https://forums.raspberrypi.com/viewtopic.php?t=314334
			if (_pio_info_g.mov_status_sel == true) {	// TX FIFO
				if (_pio_info_g.txfifo_num < _pio_info_g.mov_status_val)
					src_val	= 0xFFFFFFFF;
				else
					src_val	= 0;
			}
			else {	// RX FIFO
				if (_pio_info_g.rxfifo_num < _pio_info_g.mov_status_val)
					src_val	= 0xFFFFFFFF;
				else
					src_val	= 0;
			}
			break;

		case PIO_ISR:
			src_val	= _pio_info_g.isr;
			break;

		case PIO_OSR:
//			if (_pio_info_g.osr_autopull == true && autopull_failure == false) {
//				fprintf(stderr, "pio_exec_instruction(): WARNING. Auto-pulled OSR value will be used (MOV in step %d).\n", linenum);
//			}
			src_val	= _pio_info_g.osr;
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal source (MOV in step %d).\n", linenum);
			exit(1);
		}

		// operation
		switch (op2) {
		case PIO_NONE:
			// nothing to do
			break;
		case PIO_INVERT:
			src_val	^= 0xFFFFFFFF;
			break;
		case PIO_BIT_REVERSE:
			src_val	= _pio_bitreverse(src_val);
			break;
		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal operation (MOV in step %d).\n", linenum);
			exit(1);
		}

		// destination
		switch (op1) {
		case PIO_PINS:
			pio_output_outpin_value(src_val & 0x1F);
			break;

		case PIO_X:
			_pio_info_g.x	= src_val;
			break;

		case PIO_Y:
			_pio_info_g.y	= src_val;
			break;

		case PIO_EXEC:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
fprintf(stderr, "pio_exec_instruction(): ERROR. Unsupported destination EXEC (MOVE in step %d).\n", linenum);
exit(1);
			break;

		case PIO_PC:
			break;

		case PIO_ISR:
			_pio_info_g.isr			= src_val;
			_pio_info_g.isr_bitctr	= 0;			// IMPORTANT
			break;

		case PIO_OSR:
			if (_pio_info_g.osr_autopull == true) {
				fprintf(stderr, "pio_exec_instruction(): WARNING. Auto-pulled OSR value will be discarded and overwritten (MOV in step %d).\n", linenum);
			}

			_pio_info_g.osr			= src_val;
			_pio_info_g.osr_bitctr	= 0;			// IMPORTANT (full)
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (MOV in step %d).\n", linenum);
			exit(1);
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (op1 != PIO_PC) {
			(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
		}
		else {	// MOV PC (unconditional jmp)
			int		asmline;
			if (pio_get_asmline_pc(&asmline, src_val) == false) {
				fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (MOV in step %d).\n", linenum);
				exit(1);
			}
			_pio_info_g.asmline_ptr	= asmline;
		}

		if (delay > 0) { // set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	/////////////////////////////////
	// IRQ
	/////////////////////////////////
	case PIO_INST_IRQ: {
		bool		clr, wait, rel;
		int			irq_num;
		uint8_t		irq_setmask, irq_clrmask;

		clr		= (op1 == 1)	? true : false;
		wait	= (op2 == 1)	? true : false;
		rel		= (op4 == 1)	? true : false;

		// calc actual IRQ number
		irq_num	= op3 & 0x07;						// bit2-0
// NEEDS SPEC CHECK HERE
//		if (rel == true) {
		if (rel == true || (op3 & 0x10) != 0) {		// rel == 1 or MSB of index == 1
			irq_num	= ((irq_num + _pio_info_g.sm_id) & 0x03)		// module 4 addition to bit 1-0
						| (op3 & 0x0C);								// no effect to bit 3-2
		}
		if (0 > irq_num || irq_num > 7) {
			fprintf(stderr, "pio_exec_instruction(): Internal ERROR. Illegal irq_num (IRQ in step %d).\n", linenum);
			exit(1);
		}

		irq_setmask	= (uint8_t)1 << irq_num;
//fprintf(stderr, "setmask %02x, num %d\n", irq_setmask, irq_num);
		irq_clrmask	= irq_setmask ^ 0xFF;

		// status check
		if (_pio_info_g.irq_stalling == false) {
			if (clr == true) {
				// clear int
				_pio_info_g.irq_o		&= irq_clrmask;
				_pio_info_g.irq_i		&= irq_clrmask;		// IMPORTANT: reflect to irq_in_buf
			}
			else {
				// set int
				_pio_info_g.irq_o		|= irq_setmask;
				_pio_info_g.irq_i		|= irq_setmask;		// IMPORTANT: reflect to irq_in_buf

				if (wait == true) {
					_pio_info_g.irq_stalling	= true;
				}
			}
		}
		else {	// stalling
			// handshake; waiting change of irq_i
			if ((_pio_info_g.irq_i & irq_setmask) == 0) {
				_pio_info_g.irq_stalling	= false;
				_pio_info_g.irq_o			&= irq_clrmask;
			}
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction

		if (_pio_info_g.irq_stalling == false) {
			(_pio_info_g.asmline_ptr)++;	// increment asm buffer pointer
			if (delay > 0) { // set delay counter
				_pio_info_g.delay_timer	= delay;
			}
		}

		} break;

	/////////////////////////////////
	// SET
	/////////////////////////////////
	case PIO_INST_SET: {
		// destination
		switch (op1) {
		case PIO_PINS:
			pio_output_outpin_value(op2 & 0x1F);
			break;

		case PIO_X:
			_pio_info_g.x	= op2 & 0x1F;		// note: bit31-5 will be cleared
			break;

		case PIO_Y:
			_pio_info_g.y	= op2 & 0x1F;		// note: bit31-5 will be cleared
			break;

		case PIO_PINDIRS:
// NOT YET IMPLEMENTED 
// (NO IMPLEMENTATION PLANNED)
// (Unsupported independent pin assignment between SET and OUT)
fprintf(stderr, "pio_exec_instruction(): WARNING. Unsupported destination PINDIRS, ignored (SET in step %d).\n", linenum);
			break;

		default:
			fprintf(stderr, "pio_exec_instruction(): ERROR. Illegal destination (SET in step %d).\n", linenum);
			exit(1);
		}

		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction
		(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
		if (delay > 0) { // set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	/////////////////////////////////
	// pseudo instructions
	/////////////////////////////////
	case PIO_INST_NOP: {
		pio_output_sideset_value(sideset);
		pio_write_csv_output_regs();		// write register values AFTER executing instruction
		(_pio_info_g.asmline_ptr)++;		// increment asm buffer pointer
		if (delay > 0) { // set delay counter
			_pio_info_g.delay_timer	= delay;
		}

		} break;

	default:
		fprintf(stderr, "pio_exec_instruction(): ERROR. Internal error (INST).\n");
		exit(1);
	}

	// inc cycle counter
	(_pio_info_g.cycles)++;				// increment cycle counter
}


void pio_run_emulation(int cycles, char *file_name_in, char *file_name_out)
{
	int	ctr;

	if (_pio_emu_state_g != PIO_SIMSTATE_RUN_START) {
		fprintf(stderr, "pio_run_emulation(): ERROR. Illegal run-start position.\n");
		exit(1);
	}
	_pio_emu_state_g	= PIO_SIMSTATE_RUN_END;

	/////////////////////////////////////
	// init
	/////////////////////////////////////
	if (_pio_emu_state_g == false) {
		fprintf(stderr, "pio_run_emulation(): ERROR. No asm code is given for emulation.\n");
		exit(1);
	}
	if (file_name_in != (char *)NULL) {		// open input csv
		if ((_pio_info_g.fin = fopen(file_name_in, "rt")) == (FILE *)NULL) {
			fprintf(stderr, "pio_run_emulation(): ERROR. Cannot open input CSV file \"%s\".\n", file_name_in);
			exit(1);
		}
	}
	if (file_name_out != (char *)NULL) {	// create output csv
		if ((_pio_info_g.fout = fopen(file_name_out, "wt")) == (FILE *)NULL) {
			fprintf(stderr, "pio_run_emulation(): ERROR. Cannot create output CSV file \"%s\".\n", file_name_out);
//			if (_pio_info_g.fin != (FILE *)NULL) {
//				fclose(_pio_info_g.fin);
//			}
			exit(1);
		}
	}

	/////////////////////////////////////
	// main loop
	/////////////////////////////////////
	if (pio_check_existence_of_code() == false) {
		fprintf(stderr, "pio_run_emulation(): ERROR. No instruction exists in the main loop (wrap_target to wrap).\n");
		exit(1);
	}

//	fprintf(stderr, "\nstart emulation\n");

	pio_read_csv_input_header();
	pio_write_csv_output_header();
	for (ctr = 0; ctr < cycles; ctr++) {
		pio_exec_instruction();
	}

	/////////////////////////////////////
	// closing
	/////////////////////////////////////
	if (_pio_info_g.fin != (FILE *)NULL) {
		fclose(_pio_info_g.fin);
	}
	if (_pio_info_g.fout != (FILE *)NULL) {
		fclose(_pio_info_g.fout);
	}

	_pio_emu_state_g	= false;
}


static void pio_register_instruction(int inst, int op1, int op2, int op3, int op4, int op5, int sideset, int delay, char *str)
{
	_PIO_INST	*ap;
	char		*strbuf;
	char		*asmbuf;
	int			linenum;
	char		tmpbuf[PIO_MAX_ASMLINE_LEN * 2 + 1];
	int			sideset_num, sideset_maxval, delay_maxval;
	bool		sideset_opt;

	if (_pio_info_g.asmline_ptr >= PIO_MAX_ASMLINE_NUM) {
		fprintf(stderr, "pio_register_instruction(): ERROR. Too many assembler steps.\n");
		exit(1);
	}

	ap		= &(_pio_info_g.asmline[_pio_info_g.asmline_ptr]);
	strbuf	= ap->strbuf;
	asmbuf	= ap->asmbuf;
	linenum	= _pio_info_g.asmline_ptr + 1;

	sideset_num		= _pio_info_g.sideset_num;
	sideset_maxval	= _pio_info_g.sideset_maxval;
	sideset_opt		= _pio_info_g.sideset_opt;
	delay_maxval	= _pio_info_g.delay_maxval;

	/////////////////////////////////////
	// copy contents
	/////////////////////////////////////
	ap->used		= true;
	ap->code_line	= linenum;

//	ap->addr		= _pio_info_g.inst_ptr;
	if (_pio_info_g.origin == PIO_UNUSE)
		ap->addr	= _pio_info_g.inst_ptr;
	else
		ap->addr	= (_pio_info_g.inst_ptr + _pio_info_g.origin) & 0x3F;

	ap->inst_type	= inst;
	ap->operand1	= op1;
	ap->operand2	= op2;
	ap->operand3	= op3;
	ap->operand4	= op4;
	ap->operand5	= op5;
	ap->sideset		= sideset;
	ap->delay		= delay;
	if (str != (char *)NULL) {
		strcpy(strbuf, str);
	}

	/////////////////////////////////////
	// create assembler line
	/////////////////////////////////////
	if (_pio_info_g.wrap_line != PIO_UNUSE) {
		fprintf(stderr, "pio_register_instruction(): ERROR. No statement is allowed after \".wrap\".\n");	//, linenum);
		exit(1);
	}

	switch (inst) {
	/////////////////////////////////
	// JMP
	/////////////////////////////////
	case PIO_INST_JMP:
		sprintf(asmbuf, "jmp");

		// condition
		switch (op1) {
		case PIO_ALWAYS:
			strcat(asmbuf, "\t");
			break;
		case PIO_X_EQ_0:
			strcat(asmbuf, "\t!x\t");
			break;
		case PIO_X_NEQ_0_DEC:
			strcat(asmbuf, "\tx--\t");
			break;
		case PIO_Y_EQ_0:
			strcat(asmbuf, "\t!y\t");
			break;
		case PIO_Y_NEQ_0_DEC:
			strcat(asmbuf, "\ty--\t");
			break;
		case PIO_X_NEQ_Y:
			strcat(asmbuf, "\tx!=y\t");
			break;
		case PIO_PIN:
			strcat(asmbuf, "\tpin\t");
			break;
		case PIO_OSRE_NOTEMPTY:
			strcat(asmbuf, "\t!osre\t");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal condition (JMP in step %d).\n", linenum);
			exit(1);
		}

		// address
		sprintf(tmpbuf, "%s%s", asmbuf, str);
		strcpy(asmbuf, tmpbuf);

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// WAIT
	/////////////////////////////////
	case PIO_INST_WAIT:
		sprintf(asmbuf, "wait");

		// polarity
		if (op1 == 0) {
			strcat(asmbuf, "\t0");
		}
		else {
			strcat(asmbuf, "\t1");
		}

		// source
		switch (op2) {
		case PIO_GPIO:
			strcat(asmbuf, " gpio");
			break;
		case PIO_PIN:
			strcat(asmbuf, " pin");
			break;
		case PIO_IRQ:
			strcat(asmbuf, " irq");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal source (WAIT in step %d).\n", linenum);
			exit(1);
		}

		// index
		sprintf(tmpbuf, " 0x%02x", op3);
		strcat(asmbuf, tmpbuf);

		// rel
		if (op4 == 1) {
			strcat(asmbuf, " _rel");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// IN
	/////////////////////////////////
	case PIO_INST_IN:
		sprintf(asmbuf, "in");

		// source
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_NULL:
			strcat(asmbuf, "\tnull");
			break;
		case PIO_ISR:
			strcat(asmbuf, "\tisr");
			break;
		case PIO_OSR:
			strcat(asmbuf, "\tosr");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal source (IN in step %d).\n", linenum);
			exit(1);
		}

		// bitcount
		if (op2 >= 1 && op2 <= 32) {
			sprintf(tmpbuf, " 0x%02x", op2);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal bit count (IN in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// OUT
	/////////////////////////////////
	case PIO_INST_OUT:
		sprintf(asmbuf, "out");

		// destination
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_NULL:
			strcat(asmbuf, "\tnull");
			break;
		case PIO_PINDIRS:
			strcat(asmbuf, "\tpindirs");
			break;
		case PIO_PC:
			strcat(asmbuf, "\tpc");
			break;
		case PIO_ISR:
			strcat(asmbuf, "\tisr");
			break;
		case PIO_EXEC:
			strcat(asmbuf, "\texec");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal destination (OUT in step %d).\n", linenum);
			exit(1);
		}

		// bitcount
		if (op2 >= 1 && op2 <= 32) {
			sprintf(tmpbuf, " 0x%02x", op2);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal bit count (OUT in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// PUSH
	/////////////////////////////////
	case PIO_INST_PUSH:
		sprintf(asmbuf, "push");

		// iffull
		if (op1 == 1) {
			strcat(asmbuf, "\tiffull ");
		}
		else {
			strcat(asmbuf, "\t");
		}

		// block
		if (op2 == 0) {
			strcat(asmbuf, "noblock");
		}
		else {
			strcat(asmbuf, "block");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// PULL
	/////////////////////////////////
	case PIO_INST_PULL:
		sprintf(asmbuf, "pull");

		// ifempty
		if (op1 == 1) {
			strcat(asmbuf, "\tifempty ");
		}
		else {
			strcat(asmbuf, "\t");
		}

		// block
		if (op2 == 0) {
			strcat(asmbuf, "noblock");
		}
		else {
			strcat(asmbuf, "block");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// MOV
	/////////////////////////////////
	case PIO_INST_MOV:
		sprintf(asmbuf, "mov");

		// destination
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_EXEC:
			strcat(asmbuf, "\texec");
			break;
		case PIO_PC:
			strcat(asmbuf, "\tpc");
			break;
		case PIO_ISR:
			strcat(asmbuf, "\tisr");
			break;
		case PIO_OSR:
			strcat(asmbuf, "\tosr");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal destination (MOV in step %d).\n", linenum);
			exit(1);
		}

		// operation
		switch (op2) {
		case PIO_NONE:
			strcat(asmbuf, " ");
			break;
		case PIO_INVERT:
			strcat(asmbuf, " !");
			break;
		case PIO_BIT_REVERSE:
			strcat(asmbuf, " ::");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal operation (MOV in step %d).\n", linenum);
			exit(1);
		}

		// source
		switch (op3) {
		case PIO_PINS:
			strcat(asmbuf, "pins");
			break;
		case PIO_X:
			strcat(asmbuf, "x");
			break;
		case PIO_Y:
			strcat(asmbuf, "y");
			break;
		case PIO_NULL:
			strcat(asmbuf, "null");
			break;
		case PIO_STATUS:
			strcat(asmbuf, "status");
			break;
		case PIO_ISR:
			strcat(asmbuf, "isr");
			break;
		case PIO_OSR:
			strcat(asmbuf, "osr");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal source (MOV in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// IRQ
	/////////////////////////////////
	case PIO_INST_IRQ:
		sprintf(asmbuf, "irq");

		// clr
		if (op1 == 1) {
			strcat(asmbuf, "\tclear");
			if (op2 == 1) {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal wait-condition (IRQ in step %d).\n", linenum);
				exit(1);
			}
		}
		else {
			// NOTE: Instructions "irq" and "irq set" are written as "irq nowait".
			if (op2 == 0)
				strcat(asmbuf, "\tnowait");
			else
				strcat(asmbuf, "\twait");
		}

		// irq_num
		if (op3 >= 0 && op3 <= 7) {
			sprintf(tmpbuf, " %d", op3);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal irq_num (IRQ in step %d).\n", linenum);
			exit(1);
		}

		// rel
		if (op4 == 1) {
			strcat(asmbuf, " rel");
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// SET
	/////////////////////////////////
	case PIO_INST_SET:
		sprintf(asmbuf, "set");

		// destination
		switch (op1) {
		case PIO_PINS:
			strcat(asmbuf, "\tpins");
			break;
		case PIO_X:
			strcat(asmbuf, "\tx");
			break;
		case PIO_Y:
			strcat(asmbuf, "\ty");
			break;
		case PIO_PINDIRS:
			strcat(asmbuf, "\tpindirs");
			break;
		default:
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal destination (SET in step %d).\n", linenum);
			exit(1);
		}

		// data
		if (op2 >= 0 && op2 <= 31) {
			sprintf(tmpbuf, " 0x%02x", op2);
			strcat(asmbuf, tmpbuf);
		}
		else {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal data (SET in step %d).\n", linenum);
			exit(1);
		}

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	/////////////////////////////////
	// pseudo instructions
	/////////////////////////////////
	case PIO_INST_COMMENT:
		sprintf(asmbuf, "; %s", strbuf);
		break;

	case PIO_INST_LABEL:
		sprintf(asmbuf, "%s:", strbuf);
		break;

	case PIO_INST_NOP:
		sprintf(asmbuf, "nop");

		// sideset/delay
		if (sideset != PIO_UNUSE) {
			if (sideset >= 0 && sideset <= sideset_maxval) {
				sprintf(tmpbuf, "\tside 0x%02x", sideset);
				strcat(asmbuf, tmpbuf);
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal sideset value in step %d. (max %d)\n", linenum, sideset_maxval);
				exit(1);
			}
		}
		else if (sideset_num > 0 && sideset_opt == false) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Missing sideset value in step %d.\n", linenum);
			exit(1);
		}

		if (delay != PIO_UNUSE) {
			if (delay >= 0 && delay <= delay_maxval) {
				if (delay > 0) {
					sprintf(tmpbuf, "\t[%d]", delay);
					strcat(asmbuf, tmpbuf);
				}
			}
			else {
				fprintf(stderr, "pio_register_instruction(): ERROR. Illegal delay value in step %d. (max %d)\n", linenum, delay_maxval);
				exit(1);
			}
		}

		// check # of instructions
		if (_pio_info_g.origin == PIO_UNUSE) {
			_pio_info_g.origin	= 0;
		}

		if (_pio_info_g.inst_ptr >= PIO_MAX_INST_NUM) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Too many instructions.\n");
			exit(1);
		}
		else {
			(_pio_info_g.inst_ptr)++;
		}
		break;

	case PIO_INST_WRAP_TARGET:
		sprintf(asmbuf, ".wrap_target");

		if (_pio_info_g.wrap_target_line != PIO_UNUSE) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Multiple wrap_targets are written.\n");	//, linenum);
			exit(1);
		}
		_pio_info_g.wrap_target_line	= linenum;

		break;

	case PIO_INST_WRAP:
		sprintf(asmbuf, ".wrap");

		_pio_info_g.wrap_line			= linenum;
		break;

	case PIO_INST_ORIGIN:
		sprintf(asmbuf, ".origin %d", op1);

		if (_pio_info_g.origin != PIO_UNUSE) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal origin statement location.\n");
			exit(1);
		}
		if (op1 < 0 || op1 > 31) {
			fprintf(stderr, "pio_register_instruction(): ERROR. Illegal origin value.\n");
			exit(1);
		}
		_pio_info_g.origin	= op1;
		break;

	default:
		fprintf(stderr, "pio_register_instruction(): ERROR. Internal error (INST).\n");
		exit(1);
	}

	/////////////////////////////////////
	// increment asm buffer pointer
	/////////////////////////////////////
	(_pio_info_g.asmline_ptr)++;
}


void pio_jmp(int cond, char *lbl, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_JMP, cond, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, lbl);
}


void pio_wait(bool polarity, int src, int index, bool rel, int sideset, int delay)
{
	int	polarity_i	= (polarity == true)	? 1 : 0;
	int	rel_i		= (rel == true)			? 1 : 0;
	pio_register_instruction(PIO_INST_WAIT, polarity_i, src, index, rel_i, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_in(int src, int bitcount, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_IN, src, bitcount, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_out(int dest, int bitcount, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_OUT, dest, bitcount, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_push(bool iffull, bool block, int sideset, int delay)
{
	int	iffull_i	= (iffull == true)	? 1 : 0;
	int	block_i		= (block == true)	? 1 : 0;
	pio_register_instruction(PIO_INST_PUSH, iffull_i, block_i, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_pull(bool ifempty, bool block, int sideset, int delay)
{
	int	ifempty_i	= (ifempty == true)	? 1 : 0;
	int	block_i		= (block == true)	? 1 : 0;
	pio_register_instruction(PIO_INST_PULL, ifempty_i, block_i, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_mov(int dest, int op, int src, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_MOV, dest, op, src, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_irq(bool clr, bool wait, int index, bool rel, int sideset, int delay)
{
	int	clr_i	= (clr == true)		? 1 : 0;
	int	wait_i	= (wait == true)	? 1 : 0;
	int	rel_i	= (rel == true)		? 1 : 0;
	pio_register_instruction(PIO_INST_IRQ, clr_i, wait_i, index, rel_i, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_set(int dest, int data, int sideset, int delay)
{
	pio_register_instruction(PIO_INST_SET, dest, data, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_comment(char *string)
{
	pio_register_instruction(PIO_INST_COMMENT, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, string);
}


void pio_label(char *lbl)
{
	pio_register_instruction(PIO_INST_LABEL, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, lbl);
}


void pio_nop(int sideset, int delay)
{
	pio_register_instruction(PIO_INST_NOP, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, sideset, delay, (char *)NULL);
}


void pio_wrap_target(void)
{
	pio_register_instruction(PIO_INST_WRAP_TARGET, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, (char *)NULL);
}


void pio_wrap(void)
{
	pio_register_instruction(PIO_INST_WRAP, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, (char *)NULL);
}


void pio_origin(int addr)
{
	pio_register_instruction(PIO_INST_ORIGIN, addr, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, PIO_UNUSE, (char *)NULL);
}

#endif	// PICOPIO_EMU
// end of file
