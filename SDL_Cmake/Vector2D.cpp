//
//  Vector2D.cpp
//  SDL_App
//
//  Created by Mikami Kirigaya on 2024-03-06.
//

#include "Vector2D.h"

Vector2D::Vector2D(){
    x=0.0f;
    y=0.0f;
}

Vector2D::Vector2D(float x,float y){
    this->x=x;
    this->y=y;
}

Vector2D& Vector2D::Add(const Vector2D& vec){
    this->x+=vec.x;
    this->y+=vec.y;
    return *this;
}
Vector2D& Vector2D::Subtract(const Vector2D& vec){
    this->x-=vec.x;
    this->y-=vec.y;
    return *this;
}
Vector2D& Vector2D::Mutiply(const Vector2D& vec){
    this->x*=vec.x;
    this->y*=vec.y;
    return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec){
    this->x/=vec.x;
    this->y/=vec.y;
    return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2){//overload operators here
    return v1.Add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2){
    return v1.Subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2){
    return v1.Mutiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2){
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec){
    return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec){
    return this->Subtract(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec){
    return this->Mutiply(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec){
    return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i){
    this->x *=i;
    this->y *=i;//when used override, and can it even use overriden operators here?
    return *this;
}

Vector2D& Vector2D::Zero(){
    this->x=0.0f;
    this->y=0.0f;
    
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec){
    stream << "Vec2D("<<vec.x<<", "<<vec.y<< " )";
    return stream;
}
