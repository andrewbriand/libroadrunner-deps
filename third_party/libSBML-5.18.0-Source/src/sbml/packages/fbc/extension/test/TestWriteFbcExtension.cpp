/**
 * @file    TestWriteFbcExtension.cpp
 * @brief   Unit tests of writing FbcExtension
 * @author  Akiya Jouraku
 */

#include <limits>

#include <iostream>
#include <check.h>
#include <sbml/SBMLTypes.h>
#include <sbml/extension/SBMLExtensionRegistry.h>
#include <sbml/packages/fbc/extension/FbcModelPlugin.h>
#include <sbml/packages/fbc/extension/FbcExtension.h>
#include <sbml/packages/fbc/common/FbcExtensionTypes.h>

#include <sbml/conversion/ConversionProperties.h>

#include <string>

/** @cond doxygenIgnored */

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

/** @endcond doxygenIgnored */

CK_CPPSTART
extern char *TestDataDirectory;

static string FBC_XMLNS_L3V1V1;
static FbcExtension* G;
static FbcPkgNamespaces* GNS;

void
WriteFbcExtensionTest_setup(void)
{
  try
  {
    G = new FbcExtension();
    GNS = new FbcPkgNamespaces();
    FBC_XMLNS_L3V1V1 = GNS->getURI();
  }
  catch (...)
  {
    fail("Failed to create a FbcExtension object");
  }
}

void
WriteFbcExtensionTest_teardown(void)
{
  delete G;
  delete GNS;
}

START_TEST(test_FbcExtension_create_and_write_geneassociation)
{
  FbcPkgNamespaces *sbmlns = new FbcPkgNamespaces(3, 1, 1);

  // create the document

  SBMLDocument document(sbmlns);

  // create the Model

  Model* model = document.createModel();

  // create the Compartment

  Compartment* compartment = model->createCompartment();
  compartment->setId("compartment");
  compartment->setConstant(true);
  compartment->setSize(1);

  // create the Species

  Species* species = model->createSpecies();
  species->setId("Node1");
  species->setCompartment("compartment");
  species->setBoundaryCondition(false);

  species = model->createSpecies();
  species->setId("Node2");
  species->setCompartment("compartment");
  species->setBoundaryCondition(false);

  Reaction* reaction = model->createReaction();
  reaction->setId("J0");
  reaction->setReversible(false);
  SpeciesReference* reactant = reaction->createReactant();
  reactant->setSpecies("Node0");
  reactant->setStoichiometry(1);
  SpeciesReference* product = reaction->createProduct();
  product->setSpecies("Node1");
  product->setStoichiometry(1);

  // use fbc

  FbcModelPlugin* mplugin = static_cast<FbcModelPlugin*>(model->getPlugin("fbc"));

  fail_unless(mplugin != NULL);

  FluxBound* bound = mplugin->createFluxBound();

  bound->setId("bound1");
  bound->setReaction("J0");
  bound->setOperation("equal");
  bound->setValue(10);

  Objective* objective = mplugin->createObjective();
  objective->setId("obj1");
  objective->setType("maximize");

  FluxObjective* fluxObjective = objective->createFluxObjective();
  fluxObjective->setReaction("J0");
  fluxObjective->setCoefficient(1);

  GeneAssociation* ga = mplugin->createGeneAssociation();
  ga->setId("ga1");
  ga->setReaction("J0");

  Association* test = Association::parseInfixAssociation("(b1443) and (b1442) and (b1440) and (b1441) or (b1123) and (b1124) and (b1125) and (b1126)");
  Association* test2 = Association::parseInfixAssociation(" ( ( ( (b1443 and b1442)  and b1440)  and b1441)  or  ( ( (b1123 and b1124)  and b1125)  and b1126) ) ");

  fail_unless(test->toInfix() == test2->toInfix());
  delete test;
  delete test2;

  Association association(sbmlns);
  association.setType(OR_ASSOCIATION);
  association.addGene("b111");
  association.addGene("b112");

  ga->setAssociation(&association);

  string s1 = writeSBMLToStdString(&document);

  // check clone()

  SBMLDocument document2 = document;
  string s2 = writeSBMLToStdString(&document2);
  fail_unless(s1 == s2);

  // check operator=

  Model m = *(document.getModel());
  document2.setModel(&m);
  s2 = writeSBMLToStdString(&document2);
  fail_unless(s1 == s2);

  delete sbmlns;
}
END_TEST

START_TEST(test_FbcExtension_create_and_write_L3V1V1)
{
  FbcPkgNamespaces *sbmlns = new FbcPkgNamespaces(3, 1, 1);

  // create the document

  SBMLDocument *document = new SBMLDocument(sbmlns);
  delete sbmlns;

  // create the Model

  Model* model = document->createModel();

  // create the Compartment

  Compartment* compartment = model->createCompartment();
  compartment->setId("compartment");
  compartment->setConstant(true);
  compartment->setSize(1);

  // create the Species

  Species* species = model->createSpecies();
  species->setId("Node1");
  species->setCompartment("compartment");
  species->setBoundaryCondition(false);

  species = model->createSpecies();
  species->setId("Node2");
  species->setCompartment("compartment");
  species->setBoundaryCondition(false);

  Reaction* reaction = model->createReaction();
  reaction->setId("J0");
  reaction->setReversible(false);
  SpeciesReference* reactant = reaction->createReactant();
  reactant->setSpecies("Node0");
  reactant->setStoichiometry(1);
  SpeciesReference* product = reaction->createProduct();
  product->setSpecies("Node1");
  product->setStoichiometry(1);

  // use fbc

  FbcModelPlugin* mplugin = static_cast<FbcModelPlugin*>(model->getPlugin("fbc"));

  fail_unless(mplugin != NULL);

  FluxBound* bound = mplugin->createFluxBound();

  bound->setId("bound1");
  bound->setReaction("J0");
  bound->setOperation("equal");
  bound->setValue(10);

  Objective* objective = mplugin->createObjective();
  objective->setId("obj1");
  objective->setType("maximize");

  fail_unless(mplugin->unsetActiveObjectiveId() == LIBSBML_OPERATION_SUCCESS);
  fail_unless(mplugin->setActiveObjectiveId("obj1") == LIBSBML_OPERATION_SUCCESS);

  FluxObjective* fluxObjective = objective->createFluxObjective();
  fluxObjective->setReaction("J0");
  fluxObjective->setCoefficient(1);

  string s1 = writeSBMLToStdString(document);

  // check clone()

  SBMLDocument* document2 = document->clone();
  string s2 = writeSBMLToStdString(document2);
  fail_unless(s1 == s2);

  // check operator=

  Model m = *(document->getModel());
  document2->setModel(&m);
  s2 = writeSBMLToStdString(document2);

  fail_unless(s1 == s2);
  delete document2;

  delete document;
}
END_TEST

START_TEST(test_FbcExtension_convert_and_write)
{
  string file(TestDataDirectory);
  file += "/fbc_ga_example.xml";

  SBMLDocument* document = readSBMLFromFile(file.c_str());
  document->printErrors();
  fail_unless(document->getNumErrors(LIBSBML_SEV_ERROR) == 0);
  fail_unless(document->getModel() != NULL);

  // convert to v2
  {
    ConversionProperties props;
    props.addOption("convert fbc v1 to fbc v2", true);
    props.addOption("strict", true);

    int result = document->convert(props);

    // ensure that all is well with the model
    fail_unless(result == LIBSBML_OPERATION_SUCCESS);
    fail_unless(document->getLevel() == 3);
    fail_unless(document->getVersion() == 1);
    fail_unless(document->getPlugin("fbc") != NULL);
    fail_unless(document->getPlugin("fbc")->getPackageVersion() == 2);
  }

  // ensure that all the v1 stuff is no longer there
  FbcModelPlugin* mplug = dynamic_cast<FbcModelPlugin*>(
    document->getModel()->getPlugin("fbc"));

  fail_unless(mplug != NULL);

  fail_unless(mplug->isSetStrict());
  fail_unless(mplug->getNumGeneAssociations() == 0);
  fail_unless(mplug->getNumFluxBounds() == 0);


  delete document;
}
END_TEST

START_TEST(test_FbcExtension_create_and_write_new_geneassociation
)
{
  FbcPkgNamespaces *sbmlns = new FbcPkgNamespaces(3, 1, 2);

  // create the document

  SBMLDocument document(sbmlns);
  document.setConsistencyChecks(LIBSBML_CAT_UNITS_CONSISTENCY, false);
  document.setConsistencyChecks(LIBSBML_CAT_MODELING_PRACTICE, false);

  // create the Model

  Model* model = document.createModel();

  // create the Compartment

  Compartment* compartment = model->createCompartment();
  compartment->setId("compartment");
  compartment->setConstant(true);
  compartment->setSize(1);

  // create the Species

  Species* species = model->createSpecies();
  species->setId("Node1");
  species->setCompartment("compartment");
  species->setBoundaryCondition(false);

  species = model->createSpecies();
  species->setId("Node2");
  species->setCompartment("compartment");
  species->setBoundaryCondition(false);

  Reaction* reaction = model->createReaction();
  reaction->setId("J0");
  reaction->setReversible(false);
  SpeciesReference* reactant = reaction->createReactant();
  reactant->setSpecies("Node0");
  reactant->setStoichiometry(1);
  SpeciesReference* product = reaction->createProduct();
  product->setSpecies("Node1");
  product->setStoichiometry(1);

  // use fbc

  FbcModelPlugin* mplugin = static_cast<FbcModelPlugin*>(model->getPlugin("fbc"));

  fail_unless(mplugin != NULL);

  FluxBound* bound = mplugin->createFluxBound();

  bound->setId("bound1");
  bound->setReaction("J0");
  bound->setOperation("equal");
  bound->setValue(10);

  Objective* objective = mplugin->createObjective();
  objective->setId("obj1");
  objective->setType("maximize");

  FluxObjective* fluxObjective = objective->createFluxObjective();
  fluxObjective->setReaction("J0");
  fluxObjective->setCoefficient(1);

  FbcReactionPlugin* rplug = dynamic_cast<FbcReactionPlugin*>(reaction->getPlugin("fbc"));
  fail_unless(rplug != NULL);

  GeneProductAssociation * ga = rplug->createGeneProductAssociation();
  ga->setId("ga1");
  ga->setAssociation("MG_077 AND MG_321 AND MG_080 AND MG_078 AND MG_079");
  fail_unless(ga->getAssociation() != NULL);

  fail_unless(mplugin->getNumGeneProducts() == 5);

  ga->setAssociation("MG_077 AND MG_321 AND MG_080 AND MG_078 AND MG_079");
  fail_unless(ga->getAssociation() != NULL);

  fail_unless(mplugin->getNumGeneProducts() == 5);


  delete sbmlns;

}
END_TEST

Suite *
create_suite_WriteFbcExtension(void)
{
  Suite *suite = suite_create("WriteFbcExtension");
  TCase *tcase = tcase_create("WriteFbcExtension");

  tcase_add_checked_fixture(tcase, WriteFbcExtensionTest_setup, WriteFbcExtensionTest_teardown);

  tcase_add_test(tcase, test_FbcExtension_create_and_write_L3V1V1);
  tcase_add_test(tcase, test_FbcExtension_create_and_write_geneassociation);
  tcase_add_test(tcase, test_FbcExtension_convert_and_write);
  tcase_add_test(tcase, test_FbcExtension_create_and_write_new_geneassociation);
  suite_add_tcase(suite, tcase);

  return suite;
}

CK_CPPEND
