from rocksdb_python import Options, PyDB, ReadOptions, WriteOptions


def test_db():
    options = Options()
    options.IncreaseParallelism()
    options.create_if_missing = True

    db = PyDB(options, "./test.db")
    db.Put(WriteOptions(), b"key", b"value")
    v = db.Get(ReadOptions(), b"key")
    assert v == b"value"
