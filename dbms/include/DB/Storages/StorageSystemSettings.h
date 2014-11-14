#pragma once

#include <Poco/SharedPtr.h>

#include <DB/Storages/IStorage.h>
#include <DB/Interpreters/Context.h>


namespace DB
{

using Poco::SharedPtr;


/** Реализует системную таблицу settings, которая позволяет получить информацию о текущих настройках.
  */
class StorageSystemSettings : public IStorage
{
public:
	static StoragePtr create(const std::string & name_, const Context & context_);

	std::string getName() const override { return "SystemSettings"; }
	std::string getTableName() const override { return name; }

	const NamesAndTypesList & getColumnsListImpl() const override { return columns; }

	BlockInputStreams read(
		const Names & column_names,
		ASTPtr query,
		const Settings & settings,
		QueryProcessingStage::Enum & processed_stage,
		size_t max_block_size = DEFAULT_BLOCK_SIZE,
		unsigned threads = 1) override;

private:
	const std::string name;
	const Context & context;
	NamesAndTypesList columns;

	StorageSystemSettings(const std::string & name_, const Context & context_);
};

}