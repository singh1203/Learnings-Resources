package main

import (
	"log"
	"math/big"
	"os"
	"path/filepath"

	"github.com/apache/arrow-go/v18/arrow"
	"github.com/apache/arrow-go/v18/arrow/array"
	"github.com/apache/arrow-go/v18/arrow/decimal128"
	"github.com/apache/arrow-go/v18/arrow/memory"
	"github.com/apache/arrow-go/v18/parquet"
	"github.com/apache/arrow-go/v18/parquet/compress"
	"github.com/apache/arrow-go/v18/parquet/pqarrow"
)


func main() {
	outputPath, err := os.Getwd()
	if err != nil {
		log.Println(err)
	}

	testDictFile := filepath.Join(outputPath, "test_dict.parquet")
	testPlainFile := filepath.Join(outputPath, "test_plain.parquet")

	arrScheme := arrow.NewSchema([]arrow.Field{
		{Name: "testdecimalnullable", Type: &arrow.Decimal128Type{Precision: 38, Scale: 9}, Nullable: true},
		{Name: "testdecimalrequired", Type: &arrow.Decimal128Type{Precision: 38, Scale: 9}, Nullable: false},
	}, nil)

	rb := array.NewRecordBuilder(memory.DefaultAllocator, arrScheme)
	defer rb.Release()

	rb.Field(0).AppendNull()
	rb.Field(0).(*array.Decimal128Builder).Append(decimal128.FromBigInt(big.NewInt(123)))
	rb.Field(1).AppendNull()
	rb.Field(1).(*array.Decimal128Builder).Append(decimal128.FromBigInt(big.NewInt(456)))

	record := rb.NewRecord()
	defer record.Release()

	// write to parquet file
	useDictEncoder := true
	writeToParquetFile(testDictFile, record, useDictEncoder)

	useDictEncoder = false
	writeToParquetFile(testPlainFile, record, useDictEncoder)
}

func writeToParquetFile(filePath string, record arrow.Record, useDictEncoder bool) {
	file, err := os.OpenFile(filePath, os.O_CREATE|os.O_RDWR|os.O_TRUNC, 0664)
	if err != nil {
		log.Fatal(err.Error())
	}

	defer file.Close()

	var (
		writerProps = parquet.NewWriterProperties(
			parquet.WithCompression(compress.Codecs.Snappy),
			parquet.WithVersion(parquet.V1_0),
			parquet.WithDictionaryDefault(useDictEncoder),
		)
		arrowProps = pqarrow.NewArrowWriterProperties(pqarrow.WithStoreSchema())
	)

	fileWriter, err := pqarrow.NewFileWriter(record.Schema(), file, writerProps, arrowProps)
	if err != nil {
		log.Fatal(err.Error())
	}

	defer fileWriter.Close()

	err = fileWriter.WriteBuffered(record)
	if err != nil {
		log.Fatal(err.Error())
	}
}

