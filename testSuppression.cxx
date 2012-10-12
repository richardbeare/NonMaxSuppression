#include <iomanip>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkChangeInformationImageFilter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkNonMaxSuppressionImageFilter.h"
#include "itkTimeProbe.h"
#include "itkMultiThreader.h"


int main(int argc, char * argv[])
{
  //itk::MultiThreader::SetGlobalMaximumNumberOfThreads(1);
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< float, dim > IType;
  typedef itk::Image< PType, dim > OType;


  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );
  reader->Update();

  typedef itk::NonMaxSuppressionImageFilter< IType,OType > FilterType;

  FilterType::Pointer filter = FilterType::New();


  filter->SetInput( reader->GetOutput() );
  filter->Update();

  typedef itk::ImageFileWriter< OType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput( filter->GetOutput() );
  writer->SetFileName( argv[2] );
  writer->Update();
  return EXIT_SUCCESS;
}

