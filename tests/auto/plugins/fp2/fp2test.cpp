/******************************************************************************
**
** Copyright (C) 2009-2012 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#include "fp2test.h"

#include <boost/range/algorithm.hpp>

#include <chemkit/molecule.h>
#include <chemkit/fingerprint.h>

void Fp2Test::initTestCase()
{
    // verify that the fp2 plugin registered itself correctly
    QVERIFY(boost::count(chemkit::Fingerprint::fingerprints(), "fp2") == 1);
}

void Fp2Test::name()
{
    chemkit::Fingerprint *fingerprint = chemkit::Fingerprint::create("fp2");
    QVERIFY(fingerprint != 0);
    QCOMPARE(fingerprint->name(), std::string("fp2"));
    delete fingerprint;
}

// data generated via the following openbabel invocation
// echo "SMILES" | babel -ismi -ofpt -xfFP2 -xh
void Fp2Test::test_data()
{
    QTest::addColumn<QString>("smiles");
    QTest::addColumn<QString>("fp2_hex");

    QTest::newRow("methane") << "C" <<
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000";
    QTest::newRow("ethane") << "CC" <<
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 40000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000";
    QTest::newRow("ethanol") << "CCO" <<
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 40000000 "
        "00000000 00000000 00000000 00080008 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000";
    QTest::newRow("octanol") << "CCCCCCCCO" <<
        "00000000 01000000 00000000 00000000 00080000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 40000000 "
        "00000000 00800000 00000000 00080008 00000000 00000000 "
        "00402000 00000001 00000000 00000000 01000000 00000010 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00020000 00000000";
    QTest::newRow("serine") << "C([C@@H](C(=O)O)N)O" <<
        "00000000 00000000 00000000 00000400 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 40003000 "
        "10008000 00000000 00000000 00080008 00000000 00000000 "
        "01000000 00000000 00000000 00000a00 03000000 00000010 "
        "00000000 00000000 00000000 00000000 00000000 00040000 "
        "00000000 00000000";
    QTest::newRow("nmda") << "CN[C@H](CC(O)=O)C(O)=O" <<
        "00040000 00000000 00100000 00000400 00200080 00000000 "
        "00000000 00000000 00000000 00000000 00200000 40003000 "
        "0c008000 00000000 00000000 00080008 00000000 00000000 "
        "00c00010 00000001 00000000 10000a00 03000080 00000010 "
        "00000000 00000000 00000000 00000000 00000002 00040000 "
        "00004000 00000200";
    QTest::newRow("phenol") << "c1ccccc1O" <<
        "00000000 00000008 20000000 00000200 00000000 00000000 "
        "02000000 00000000 00000000 00000840 00000000 00008000 "
        "00000002 00000000 00000000 00000008 00000000 00000000 "
        "00000000 00020000 00000000 08000000 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00020000 "
        "00000000 00000000";
    QTest::newRow("uracil") << "O=C1NC=CC(=O)N1" <<
        "00000002 00000000 00000000 02000600 00000000 00004000 "
        "00000000 00000000 06000100 00000020 04000004 00000000 "
        "00008000 00400000 00200000 000c0004 00000000 00008000 "
        "00400000 00000000 00000000 00000000 20800040 00100000 "
        "00040000 c0000000 20000000 00040000 00004000 00420000 "
        "40000000 00000080";
    QTest::newRow("guanine") << "c1[nH]c2c(n1)c(=O)[nH]c(n2)N" <<
        "0000000a 00801800 00080000 00000600 00000040 0000c000 "
        "0000b000 00000800 06400100 00000060 00008004 00001000 "
        "00008000 00400000 00000000 100c0004 00000000 00008000 "
        "00400000 00200000 00000100 04000040 21800840 00300004 "
        "00000000 80200000 60000000 00040000 00004008 00461000 "
        "c0000000 80000280";
    QTest::newRow("tryptophan") << "c1ccc2c(c1)c(c[nH]2)C[C@@H](C(=O)O)N" <<
        "00000002 00000800 00000100 41810610 00041000 00000000 "
        "00002000 00000000 00400800 00090840 08100004 4000b000 "
        "1c008800 00400800 00000040 000c000c 00000000 02000000 "
        "00600408 00000001 40000100 18008a08 23800040 81400010 "
        "00043801 80000000 08000000 00000000 04000000 00060002 "
        "00040200 00000420";
    QTest::newRow("cAMP") << "c1nc(c2c(n1)n(cn2)[C@H]3[C@@H]([C@H]4[C@H](O3)COP(=O)(O4)O)O)N" <<
        "0000000a 01c01800 80080510 89890e20 003800e4 0008c000 "
        "0000cc00 00003800 00404100 018000b0 0c00800c 40019004 "
        "00001000 038a0120 00081080 101eca0c 002a0020 00800000 "
        "39c00000 80205003 80080020 14000850 27800040 0c000014 "
        "10000400 40000002 0e000200 10010070 00000208 0046001c "
        "d1e80000 000180c0";
    QTest::newRow("lsd") << "CCN(CC)C(=O)C1CN(C2CC3=CNC4=CC=CC(=C34)C2=C1)C" <<
        "00000012 2910cc00 01900302 41910610 00041100 00000000 "
        "800820c0 04000403 004109c0 0019096a 08300004 51019000 "
        "98028902 00610800 00040042 400e024c 20000600 02000144 "
        "00222412 00000201 40800500 1a308608 20808040 91400018 "
        "01243000 80000801 0848284c d0000000 04404000 00260c13 "
        "24040200 02012620";
    QTest::newRow("octanitrocubane") << "C12(C3(C4(C1(C5(C2(C3(C45[N+](=O)[O-])"
                                        "[N+](=O)[O-])[N+](=O)[O-])[N+](=O)[O-])"
                                        "[N+](=O)[O-])[N+](=O)[O-])[N+](=O)[O-])"
                                        "[N+](=O)[O-]" <<
        "00000000 01000010 40000000 00000400 00000000 000000c0 "
        "0c000000 00000000 14000001 80000180 00000000 40030000 "
        "0001000c 00c00010 00000000 00000010 00000000 00000000 "
        "02002000 000c0001 00000100 30000030 00000000 00200012 "
        "10010000 00000000 00000000 00200000 00000000 00040000 "
        "00020000 01000000";
    QTest::newRow("serotonin") << "c1cc2c(cc1O)c(c[nH]2)CCN" <<
        "00000002 00000808 20000100 41010610 00041000 00000000 "
        "06002000 00000000 00400000 00090840 08000004 40008000 "
        "10000806 00400000 00000040 0004000c 00000000 02000000 "
        "00200400 00020000 40000000 18008008 20800000 81400010 "
        "00042000 80000000 08120000 00000000 04000000 00060002 "
        "00040200 00000420";
    QTest::newRow("coronene") << "c1cc2ccc3ccc4ccc5ccc6ccc1c7c2c3c4c5c67" <<
        "00000000 00000000 00000000 00000200 00000000 00000000 "
        "00000000 00000000 00000000 00000840 00000000 00008000 "
        "00000000 00000000 00000000 00000000 00000000 00000000 "
        "00000000 00000000 00000000 08000008 00000000 00000000 "
        "00000000 00000000 00000000 00000000 00000000 00020000 "
        "00000000 00000000";
    QTest::newRow("thc") << "CCCCCC1=CC2=C(C3C=C(CCC3C(O2)(C)C)C)C(=C1)O" <<
        "04004001 c3000038 2000010a 80210302 80081000 c2800000 "
        "42000005 00000642 00044900 00980848 08100000 40008840 "
        "00821002 20a00084 11000401 00082008 08800000 22108020 "
        "02682000 00022a01 80000124 08000000 01008040 00400410 "
        "00200000 c0000000 00404000 80000000 20010302 00034002 "
        "24020000 00000400";
    QTest::newRow("diazepam") << "CN1C(=O)CN=C(C2=C1C=CC(=C2)Cl)C3=CC=CC=C3" <<
        "0000c002 06440000 00200160 0c010600 40000062 04080164 "
        "14000002 01240005 00000300 20090e45 08280024 4000ac00 "
        "02108006 00108800 80060140 00180002 0224c800 03400003 "
        "08008000 00000000 40102010 3c000740 20002003 00400012 "
        "10002881 a0000000 40080018 45001080 08088098 00068403 "
        "c0000080 22020600";
    QTest::newRow("caffeine") << "CN1C=NC2=C1C(=O)N(C(=O)N2C)C" <<
        "0000002a 00801800 00080000 02010700 00080040 0000c000 "
        "00008000 00000000 06400100 800000a0 0c00800c 00000000 "
        "00009000 00400000 00280080 000c000c 00800000 00088000 "
        "00400000 00000000 80000100 10000040 21800041 00300004 "
        "00040000 c0200000 60000000 00040000 00004000 00460000 "
        "c0000000 00000280";
    QTest::newRow("paroxetine") << "c1cc(ccc1[C@@H]2CCNC[C@H]2COc3ccc4c(c3)OCO4)F" <<
        "04000001 01000208 20100108 02010700 00081000 0200001c "
        "42000000 20000000 00200a00 000808e0 48300000 50018000 "
        "00804002 01001000 11000001 002ca108 00a00000 02000084 "
        "00c80000 00120a03 00040300 18002000 010000c0 08500010 "
        "40000001 80000000 00080000 30000001 01050200 0006800a "
        "00000000 02012640";
    QTest::newRow("duloxetine") << "CNCC[C@@H](C1=CC=CS1)OC2=CC=CC3=CC=CC=C32" <<
        "04010000 04000208 20100108 20010600 00001040 02004080 "
        "02000080 00000000 00000900 004808c0 00300200 c0008080 "
        "00800012 00010000 01002001 060c2008 08200000 02000008 "
        "00800000 00020015 00002920 58080088 01100080 00c01010 "
        "02000000 06002004 00000000 90000204 00000200 0006000a "
        "48000000 00c10650";
    QTest::newRow("penicillin") << "CC1([C@@H](N2[C@H](S1)[C@@H](C2=O)NC(=O)Cc3ccccc3)C(=O)O)C" <<
        "00000000 46007000 20164360 0c310640 00000080 00000000 "
        "00201200 00000008 00000080 0a0e4840 08200001 4004b000 "
        "0f01e006 000c2101 c0180001 00480008 14000400 02000200 "
        "00400010 00400309 40000000 38200e00 03000701 87400018 "
        "00001200 80000020 00004000 00000000 0c001000 00060023 "
        "20006010 83012680";
}

void Fp2Test::test()
{
    QFETCH(QString, smiles);
    QFETCH(QString, fp2_hex);

    chemkit::Molecule molecule(smiles.toStdString(), "smiles");
    QVERIFY(!molecule.isEmpty());

    QStringList strings = fp2_hex.split(' ', QString::SkipEmptyParts);
    QCOMPARE(strings.size(), 32);

    chemkit::Bitset expected;

    // openbabel output is backwards
    for(int i = strings.size() - 1; i >= 0; i--){
        QByteArray value = QByteArray::fromHex(strings[i].toAscii());
        QCOMPARE(value.size(), 4);

        // and little-endian
        for(int j = 3; j >= 0; j--){
            unsigned char byte = value[j];

            for(size_t k = 0; k < 8; k++){
                expected.push_back(byte & (1 << k));
            }
        }
    }

    QCOMPARE(expected.size(), size_t(1024));

    chemkit::Bitset actual = molecule.fingerprint("fp2");
    QCOMPARE(actual.size(), size_t(1024));

    for(size_t i = 0; i < 1024; i++){
        if(actual[i] != expected[i]){
            qDebug() << "Value at bit" << i << "does not match.";
            qDebug() << "  Actual:" << actual[i];
            qDebug() << "  Expected:" << expected[i];
            QVERIFY(actual[i] == expected[i]);
        }
    }
}

QTEST_APPLESS_MAIN(Fp2Test)
