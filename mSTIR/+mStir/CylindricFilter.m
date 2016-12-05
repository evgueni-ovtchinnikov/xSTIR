classdef CylindricFilter < mStir.DataProcessor
    methods
        function self = CylindricFilter(filter)
            self.name = 'TruncateToCylindricalFOVImageProcessor';
            if nargin < 1
                self.handle = calllib...
                    ('mstir', 'mSTIR_newObject', self.name);
            else
                self.handle = calllib...
                    ('mutilities', 'mCopyOfObjectHandle', filter.handle);
%                    ('mstir', 'mSTIR_copyOfObject', filter.handle);
            end
        end
        function delete(self)
            if ~isempty(self.handle)
                calllib('mutilities', 'mDeleteDataHandle', self.handle)
%                calllib('mstir', 'mSTIR_deleteObject', self.handle)
                self.handle = [];
            end
        end
        function set_strictly_less_than_radius(self, flag)
            if flag
                str = 'true';
            else
                str = 'false';
            end
            mStir.setParameter(self.handle,...
                'TruncateToCylindricalFOVImageProcessor',...
                'strictly_less_than_radius', str, 'c')
        end
        function flag = get_strictly_less_than_radius(self)
            flag = mStir.parameter(self.handle,...
                'TruncateToCylindricalFOVImageProcessor',...
                'strictly_less_than_radius', 'i');
        end
    end
end