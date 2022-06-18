import pytest
from rocksdb_python import Options, PyDB, ReadOptions, WriteOptions, PyWriteBatch


def test_db():
    options = Options()
    options.IncreaseParallelism()
    options.OptimizeLevelStyleCompaction()
    options.create_if_missing = True

    db = PyDB(options, "./test.db")
    db.Put(WriteOptions(), b"key1", b"value")
    value = db.Get(ReadOptions(), b"key1")
    assert value == b"value"

    batch = PyWriteBatch()
    batch.Delete(b"key1")
    batch.Put(b"key2", value)
    db.Write(WriteOptions(), batch)

    with pytest.raises(RuntimeError) as e:
        value = db.Get(ReadOptions(), b"key1")
    assert e.value.args == ('NotFound: ',)

    value = db.Get(ReadOptions(), b"key2")
    assert value == b"value"
