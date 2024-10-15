# Summary

## Type

|                       | file         | header   | methods  | test     |
|-----------------------|--------------|----------|----------|----------|
| *non-numerical type*  |              |          |          |          |
| String                | String       | &#x2714; | &#x2714; | &#x2714; |
| Date                  | DateTime     | &#x2714; | &#x2714; | &#x2714; |
| Time                  | DateTime     | &#x2714; | &#x2714; | &#x2714; |
| DateTime              | DateTime     | &#x2714; | &#x2714; | &#x2714; |
| StaticDict            | Dict         | &#x2714; | &#x2714; | &#x2714; |
| DynamicDict           | Dict         | &#x2714; | &#x2714; | &#x2714; |
| Sheet                 | Dict         | &#x2714; | &#x2714; | &#x2714; |
|                       |              |          |          |          |
| *General Array Type*  |              |          |          |          |
| Vector                | Vector       |          |          |          |
| Array                 | Array        |          |          |          |
| TypeArray Template    |              |          |          |          |
|                       |              |          |          |          |
| *Int Arrays*          |              |          |          |          |
| IntVector             | IntVector    | &#x2714; | &#x2714; | &#x2714; |
| IntMatrix             |              |          |          |          |
| IntTensor             |              |          |          |          |
| IntArray              |              |          |          |          |
|                       |              |          |          |          |
| *Float Arrays*        |              |          |          |          |
| FloatVector           | FloatVector  | &#x2714; | &#x2714; | &#x2714; |
| FloatMatrix           |              |          |          |          |
| FloatTensor           |              |          |          |          |
| FloatArray            |              |          |          |          |
|                       |              |          |          |          |
| *Macro Template*      |              |          |          |          |
| IntVector_n macro     | IntVectorN   | &#x2714; | &#x2714; | &#x2714; |
| IntMatrix_m_n macro   | IntMatrixN   |          |          |          |
| IntTensor_p_q_r macro |              |          |          |          |
| FloatVector_n macro   | FloatVectorN | &#x2714; | &#x2714; | &#x2714; |

## Module

|              | file  | header   | methods  | test     |
|--------------|-------|----------|----------|----------|
| type defines | Basic | &#x2714; |          |          |
| basic error  | Basic | &#x2714; | &#x2714; |          |
|              |       |          |          |          |
| *Basic Type* |       |          |          |          |
| Log          | Log   | &#x2714; | &#x2714; | &#x2714; |

# Depencency

| Module   | String | DateTime |
|----------|--------|----------|
| Basic    |        |          |
| String   |        |          |
| DateTime | String |          |
| Log      | String | DateTime |
| Dict     | String |          |

|              | IntVector | IntVectorN | FloatVector |
|--------------|-----------|------------|-------------|
| IntVector    |           |            |             |
| IntVectorN   | IntVector |            |             |
| FloatVector  | IntVector |            |             |
| FloatVectorN | IntVector | IntVectorN | FloatVector |

# By file

## DateTime
