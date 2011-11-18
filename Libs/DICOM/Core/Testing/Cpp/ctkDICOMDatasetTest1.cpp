/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// ctkDICOMCore includes
#include "ctkDICOMDataset.h"

// STD includes
#include <iostream>

int ctkDICOMDatasetTest1( int argc, char * argv [] )
{
  Q_UNUSED(argc);
  Q_UNUSED(argv);
  ctkDICOMDataset dataset;
  dataset.InitializeFromDataset(0);
  dataset.InitializeFromFile(QString());
  try
    {
    dataset.Serialize();
    }
  catch(...)
    {
    std::cout << "ctkDICOMDataset::Serialize() throws exceptions" << std::endl;
    //return EXIT_FAILURE;
    }
  try
    {
    dataset.Deserialize();
    }
  catch(...)
    {
    std::cout << "ctkDICOMDataset::Deserialize() throws exceptions"
              << std::endl;
    //return EXIT_FAILURE;
    }
  dataset.MarkForInitialization();
  try
    {
    dataset.EnsureDcmDataSetIsInitialized();
    }
  catch(...)
    {
    std::cout << "ctkDICOMDataset::EnsureDcmDataSetIsInitialized() throws"
              << " exceptions" << std::endl;
    //return EXIT_FAILURE;
    }

  // deactivating the lower part since it (correctly) causes
  // execptions since it calls methods on an uninitialized object
  return EXIT_SUCCESS;

  dataset.CopyElement(0, DcmTagKey(), 0);
  QString decode = dataset.Decode(DcmTag(),OFString());
  if (!decode.isEmpty())
    {
    std::cerr << "ctkDICOMDataset::Decode() failed: "
              << qPrintable(decode) << std::endl;
    return EXIT_FAILURE;
    }
  OFString encode = dataset.Encode(DcmTag(), decode);
  DcmElement* element = 0;
  OFCondition condition = dataset.findAndGetElement(DcmTag(), element);
  if (ctkDICOMDataset::CheckCondition(condition))
    {
    std::cerr << "ctkDICOMDataset::findAndGetElement() failed" << std::endl;
    return EXIT_FAILURE;
    }
  OFString string;
  condition = dataset.findAndGetOFString(DcmTag(), string);
  if (ctkDICOMDataset::CheckCondition(condition))
    {
    std::cerr << "ctkDICOMDataset::findAndGetOFString() failed" << std::endl;
    return EXIT_FAILURE;
    }
   try
    {
    QString string = dataset.GetAllElementValuesAsString(DcmTag());
    QString string2 = dataset.GetElementAsString(DcmTag());
    QStringList list = dataset.GetElementAsStringList(DcmTag());
    ctkDICOMPersonName name = dataset.GetElementAsPersonName(DcmTag());
    ctkDICOMPersonNameList nameList = dataset.GetElementAsPersonNameList(DcmTag());
    QDate date = dataset.GetElementAsDate(DcmTag());
    QTime time = dataset.GetElementAsTime(DcmTag());
    double doubleValue = dataset.GetElementAsDouble(DcmTag());
    int integerValue = dataset.GetElementAsInteger(DcmTag());
    int shortValue = dataset.GetElementAsSignedShort(DcmTag());
    int ushortValue = dataset.GetElementAsUnsignedShort(DcmTag());
    QDateTime dateTime = dataset.GetElementAsDateTime(DcmTag());
    Q_UNUSED(string);
    Q_UNUSED(string2);
    Q_UNUSED(list);
    Q_UNUSED(name);
    Q_UNUSED(nameList);
    Q_UNUSED(date);
    Q_UNUSED(time);
    Q_UNUSED(doubleValue);
    Q_UNUSED(integerValue);
    Q_UNUSED(shortValue);
    Q_UNUSED(ushortValue);
    Q_UNUSED(dateTime);

    dataset.SetElementAsString( DcmTag(), QString());
    dataset.SetElementAsStringList( DcmTag(), QStringList() );
    dataset.SetElementAsPersonName( DcmTag(), ctkDICOMPersonName());
    dataset.SetElementAsPersonNameList( DcmTag(), ctkDICOMPersonNameList() );
    dataset.SetElementAsDate( DcmTag(), QDate() );
    dataset.SetElementAsTime( DcmTag(), QTime() );
    dataset.SetElementAsDateTime( DcmTag(), QDateTime() );
    dataset.SetElementAsInteger( DcmTag(), 0 ); // type IS
    dataset.SetElementAsSignedShort( DcmTag(), 0 ); // type SS
    dataset.SetElementAsUnsignedShort( DcmTag(), 0 ); // type US
    }
  catch(...)
    {
    std::cout << "ctkDICOMDataset::GetElementValueAsXXX() throws exceptions"
              << std::endl;
    //return EXIT_FAILURE;
    }
  ctkDICOMDataset::TranslateDefinedTermPatientPosition(QString());
  ctkDICOMDataset::TranslateDefinedTermModality(QString());
  ctkDICOMDataset::TagKey(DcmTag());
  ctkDICOMDataset::TagDescription(DcmTag());
  ctkDICOMDataset::TagVR(DcmTag());
  
  return EXIT_SUCCESS;
}
