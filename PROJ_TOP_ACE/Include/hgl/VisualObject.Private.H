		friend class ObjectControl;

	protected:

		bool visible;
		bool topmost;
		bool bottommost;

	protected:

		bool GetVisible(){return visible;}
		bool GetTopMost(){return topmost;}
		bool GetBottomMost(){return bottommost;}

		virtual void SetVisible(bool);
		virtual void SetTopMost(bool);
		virtual void SetBottomMost(bool);
