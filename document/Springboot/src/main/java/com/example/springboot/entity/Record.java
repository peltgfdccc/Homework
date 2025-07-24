package com.example.springboot.entity;

import com.baomidou.mybatisplus.annotation.IdType;
import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;


@Data
@AllArgsConstructor
@NoArgsConstructor

@TableName(value = "record")
public class Record {

    @TableId(value = "id", type = IdType.AUTO)
    private String Id;

    @TableField(value = "student_name")
    private String StudentName;
    @TableField(value = "go_date")
    private String GoDate;
    @TableField(value = "type")
    private String Type;

    public String getId() {
        return Id;
    }

    public void setId(String id) {
        Id = id;
    }

    public String getStudentName() {
        return StudentName;
    }

    public void setStudentName(String studentName) {
        StudentName = studentName;
    }

    public String getGoDate() {
        return GoDate;
    }

    public void setGoDate(String goDate) {
        GoDate = goDate;
    }

    public String getType() {
        return Type;
    }

    public void setType(String type) {
        Type = type;
    }
}
